package pub_sub

import (
	"fmt"
	"sync"
)

type Broadcaster[T any] struct {
	sub     map[<-chan T]chan T
	mu      sync.RWMutex
	stopped bool
}

func NewBroadcaster[T any]() *Broadcaster[T] {
	return &Broadcaster[T]{
		sub: make(map[<-chan T]chan T),
	}
}

// Publish sends event to all current subscribers
func (b *Broadcaster[T]) Publish(event T) error {
	b.mu.RLock()
	defer b.mu.RUnlock()
	if b.stopped {
		return fmt.Errorf("publish failed: broadcaster is stopped") // This trade off,
		// publish shouldn't return error but this is not error this is signal
		//about something went wrong could be using it for metrics or something else
	}
	for _, ch := range b.sub {
		select {
		case ch <- event:
		default:
			// What kind of production work might be done here, for example?
		}
	}
	return nil
}

// Subscribe returns a new subscriber channel
func (b *Broadcaster[T]) Subscribe(bufSize int) (<-chan T, error) {
	b.mu.Lock()
	defer b.mu.Unlock()
	if b.stopped {
		return nil, fmt.Errorf("subscription failed: broadcaster is stopped")
	}
	ch := make(chan T, bufSize)
	b.sub[ch] = ch
	return ch, nil
}

// Unsubscribe removes a subscriber
func (b *Broadcaster[T]) Unsubscribe(ch <-chan T) {
	b.mu.Lock()
	defer b.mu.Unlock()
	if inner, ok := b.sub[ch]; ok {
		close(inner)
		delete(b.sub, ch)
	}
}

// Stop closes all subscriber channels
func (b *Broadcaster[T]) Stop() {
	b.mu.Lock()
	defer b.mu.Unlock()
	for _, ch := range b.sub {
		close(ch)
	}
	b.sub = make(map[<-chan T]chan T)
	b.stopped = true
}
