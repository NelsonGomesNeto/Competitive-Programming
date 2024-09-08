package main

import (
	"fmt"
)

var n = 0
var a = []int{}

func Gcd(x, y int) int {
	for y != 0 {
		x, y = y, x%y
	}
	return x
}

func NextPermutation(a []int) bool {
	split_pos := -1
	for i := len(a) - 2; i >= 0; i-- {
		if a[i] < a[i+1] {
			split_pos = i
			break
		}
	}
	if split_pos == -1 {
		return false
	}

	// Reverse after `split_pos`
	for i, j := split_pos+1, len(a)-1; i < j; i, j = i+1, j-1 {
		a[i], a[j] = a[j], a[i]
	}

	for i := split_pos + 1; i < len(a); i++ {
		if a[split_pos] < a[i] {
			a[split_pos], a[i] = a[i], a[split_pos]
			break
		}
	}

	return true
}

func Max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func Beauty(a []int) int {
	beauty := 0
	for i := 1; i < len(a); i++ {
		beauty += Gcd(a[i-1], a[i])
	}
	return beauty
}
func Naive() int {
	ans := Beauty(a)
	for NextPermutation(a) {
		ans = Max(ans, Beauty(a))
	}
	return ans
}

var all_mask = 0
var memo = [][]int{}

func Solve(prev, mask int) int {
	if mask == all_mask {
		return 0
	}
	if memo[prev][mask] != -1 {
		return memo[prev][mask]
	}

	ans := 0
	for i := 0; i < len(a); i++ {
		if (1<<i)&mask != 0 {
			continue
		}
		to_add := 0
		if prev != n {
			to_add = Gcd(a[prev], a[i])
		}
		ans = Max(ans, Solve(i, mask|(1<<i))+to_add)
	}

	memo[prev][mask] = ans
	return ans
}

func main() {
	fmt.Scanf("%d", &n)
	all_mask = (1 << n) - 1
	for i := 0; i < n; i++ {
		a = append(a, 0)
		fmt.Scanf("%d", &a[i])
	}

	// fmt.Println(n)
	// fmt.Println(a)

	memo = make([][]int, n+1)
	for i := range memo {
		memo[i] = make([]int, 1<<n)
		for j := range memo[i] {
			memo[i][j] = -1
		}
	}
	ans := Solve(n, 0)
	fmt.Println(ans)
}
