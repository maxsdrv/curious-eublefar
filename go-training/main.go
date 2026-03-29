package main

import (
	"context"
	"errors"
	"fmt"
	"sync"
	"time"

	"go-training/fan_in"
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

func main() {
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	//s := make([]int, 10, 15)
	//s2 := s[2:8]
	//fmt.Println(s2)
	//s[2] = 100
	//fmt.Println(s2[0])

	//rateLimiter()

	/*
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
}
