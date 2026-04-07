package main

import (
	"context"
	"fmt"
	"sync"
	"time"
)

func rateLimiter() {
	request := make(chan int, 20)

	go func() {
		defer close(request)
		for i := 0; i < 15; i++ {
			request <- i
		}
	}()

	tokens := make(chan struct{}, 3)

	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	var wg sync.WaitGroup
	wg.Add(1)

	go func() {
		ticker := time.NewTicker(200 * time.Millisecond)
		defer ticker.Stop()
		defer wg.Done()
		for {
			select {
			case <-ctx.Done():
				fmt.Println("rate limiter stopped")
				return
			case <-ticker.C:
				select {
				case tokens <- struct{}{}:
					fmt.Println("token granted")
				default:
					fmt.Println("bucket full, dropping token")
				}
			}
		}
	}()

	for req := range request {
		time.Sleep(50 * time.Millisecond)
		select {
		case <-tokens:
			fmt.Printf("request %d: processing \n", req)
		default:
			fmt.Printf("request %d: refused (no tokens)\n", req)
		}
	}

	fmt.Println("all requests done")

	cancel()
	wg.Wait()
}

func printNumber(n int, wg *sync.WaitGroup) {
	defer wg.Done()
	time.Sleep(time.Second)
	fmt.Println(n)
}

func runPrintNumber() {
	var wg sync.WaitGroup

	limiter := make(chan struct{}, 3)

	for i := 1; i <= 10; i++ {
		wg.Add(1)
		go func(i int) {
			limiter <- struct{}{}
			defer func() { <-limiter }()
			defer func() {
				if r := recover(); r != nil {
					fmt.Println("panic:", r)
				}
			}()
			printNumber(i, &wg)
		}(i)
	}
	wg.Wait()
}

type Testing interface {
	Method()
}
type MyStruct struct {
}

func (m *MyStruct) Method() {
	fmt.Println("method")
}

func DoSomething(t Testing) {
	fmt.Println("Method called")
	t.Method()
}

func main() {
	_, cancel := context.WithCancel(context.Background())
	defer cancel()

	// Interface example
	//m := &MyStruct{}
	//DoSomething(m)

	//s := make([]int, 10, 15)
	//s2 := s[2:8]
	//fmt.Println(s2)
	//s[2] = 100
	//fmt.Println(s2[0])

	//rateLimiter()

	/* Worker Pool example usage:
	input := make(chan string, 3)
	input <- "INFO: hello"
	input <- "ERROR: world"
	input <- "DEBUG: sentinel"
	close(input)

	output := worker_pool.ProcessLogs(ctx, input, 10)

	for entry := range output {
		fmt.Printf("Level: %s, Message: %s\n", entry.Level, entry.Message)
	}
	*/

	/* Fain In with Error example usage:
	source1 := make(chan fan_in.Result, 2)
	source2 := make(chan fan_in.Result, 2)

	source1 <- fan_in.Result{Value: "sensor-1: 42"}
	source2 <- fan_in.Result{Value: "sensor-2: 99"}
	source1 <- fan_in.Result{Err: errors.New("sensor-1 failed")}
	close(source1)
	close(source2)

	output := fan_in.FanIn(ctx, []<-chan fan_in.Result{source1, source2})
	for r := range output {
		if r.Err != nil {
			fmt.Println("error:", r.Err)
			break
		}
		fmt.Println(r.Value)
	}
	*/

	//Pub Sub example usage:
	/*b := pub_sub.NewBroadcaster[string]()

	sub1, err := b.Subscribe(10)
	sub2, err := b.Subscribe(10)
	if err != nil {
		panic(err)
	}

	b.Publish("event-1")
	b.Publish("event-2")

	b.Unsubscribe(sub2)
	b.Publish("event-3") // only sub1 receives this

	b.Stop()

	for msg := range sub1 {
		fmt.Printf("Subscriber 1: %s\n", msg)
	}
	for msg := range sub2 {
		fmt.Printf("Subscriber 2: %s\n", msg)
	}
	*/

	runPrintNumber()
}
