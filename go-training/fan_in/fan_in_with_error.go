package fan_in

import (
	"context"
	"fmt"
	"sync"
)

type Result struct {
	Value string
	Err   error
}

func FanIn(
	ctx context.Context,
	inputs []<-chan Result,
) <-chan Result {
	fmt.Printf("FanIn started\n")

	ctx, cancel := context.WithCancel(ctx)

	output := make(chan Result)

	var wg sync.WaitGroup
	for _, input := range inputs {
		wg.Add(1)
		go func(input <-chan Result) {
			defer wg.Done()
			for {
				select {
				case <-ctx.Done():
					return
				case r, ok := <-input:
					if !ok {
						return
					}
					output <- r
					if r.Err != nil {
						cancel()
						return
					}
				}
			}
		}(input)
	}

	go func() {
		defer close(output)
		defer cancel()
		wg.Wait()
	}()

	return output
}
