package worker_pool

import (
	"context"
	"strings"
	"sync"
)

type LogEntry struct {
	Level   string
	Message string
}

func parseLine(line string) LogEntry {
	parts := strings.SplitN(line, ":", 2)
	if len(parts) != 2 {
		return LogEntry{Level: "UNKNOWN", Message: line}
	}
	return LogEntry{Level: parts[0], Message: parts[1]}
}

func ProcessLogs(
	ctx context.Context,
	input <-chan string,
	workers int,
) <-chan LogEntry {
	output := make(chan LogEntry, workers)

	var wg sync.WaitGroup
	wg.Add(workers)

	go func() {
		wg.Wait()
		close(output)
	}()

	for i := 0; i < workers; i++ {
		go func() {
			defer wg.Done()
			for {
				select {
				case <-ctx.Done():
					return
				case log, ok := <-input:
					if !ok {
						return
					}
					output <- parseLine(log)
				}
			}
		}()
	}

	return output
}
