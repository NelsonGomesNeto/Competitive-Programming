package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"sort"
	"strconv"
	"strings"
	"sync"
	"time"
)

func merge(arr []int, tmp []int, mid int) {
	hi := len(arr) - 1
	for i, j, k := 0, mid, 0; i < mid || j <= hi; k++ {
		if i >= mid {
			tmp[k] = arr[j]
			j++
		} else if j > hi {
			tmp[k] = arr[i]
			i++
		} else if arr[i] < arr[j] {
			tmp[k] = arr[i]
			i++
		} else {
			tmp[k] = arr[j]
			j++
		}
	}
	for i := 0; i <= hi; i++ {
		arr[i] = tmp[i]
	}
}

func mergeSort(arr []int, tmp []int) {
	sz := len(arr)
	if sz == 1 {
		return
	}

	mid := sz >> 1
	mergeSort(arr[:mid], tmp[:mid])
	mergeSort(arr[mid:], tmp[mid:])

	merge(arr, tmp, mid)
}

func MergeSort(arr []int) {
	tmp := make([]int, len(arr))
	mergeSort(arr, tmp)
}

var Threshold int = 1e4

func mergeSortAsync(arr []int, tmp []int) {
	sz := len(arr)
	if sz == 1 {
		return
	}

	mid := sz >> 1
	if sz < Threshold {
		mergeSort(arr[:mid], tmp[:mid])
		mergeSort(arr[mid:], tmp[mid:])
	} else {
		var wg sync.WaitGroup
		wg.Add(1)
		go func() {
			defer wg.Done()
			mergeSortAsync(arr[mid:], tmp[mid:])
		}()
		mergeSortAsync(arr[:mid], tmp[:mid])
		wg.Wait()
	}

	merge(arr, tmp, mid)
}

func MergeSortAsync(arr []int) {
	tmp := make([]int, len(arr))
	mergeSortAsync(arr, tmp)
}

func ReadArrayDirectlyFromBufio(n int) []int {
	arr := make([]int, n)
	reader := bufio.NewReader(os.Stdin)
	str, err := reader.ReadString('\n')
	if err != nil && err != io.EOF {
		fmt.Printf("err: %v\n", err)
		panic("bugou")
	}
	strs := strings.Split(str, " ")
	for i, s := range strs {
		var err error
		if strings.HasSuffix(s, "\n") {
			s = s[:len(s)-1]
		}
		arr[i], err = strconv.Atoi(s)
		if err != nil {
			fmt.Printf("err.Error() atoi: %v\n", err.Error())
		}
	}
	return arr
}

func PrintExecutionTime(start time.Time, name string) {
	elapsed := time.Since(start)
	fmt.Printf("%s: %s\n", name, elapsed)
}

var Executions int = 30

func GetAverageExecutionTime(arr []int) {
	averageTime := time.Duration(0)
	cpy := make([]int, len(arr))
	copy(cpy, arr)
	for i := 0; i < Executions; i++ {
		copy(arr, cpy)
		startTime := time.Now()
		MergeSortAsync(arr)
		// MergeSort(arr)
		elapsed := time.Since(startTime)
		averageTime += elapsed
	}
	averageTime /= time.Duration(Executions)
	fmt.Printf("MergeSort: %s\n", averageTime)

	if !sort.IntsAreSorted(arr) {
		panic("not sorted!")
	}
}

func main() {
	var n int
	fmt.Scanln(&n)
	arr := ReadArrayDirectlyFromBufio(n)

	GetAverageExecutionTime(arr)
}
