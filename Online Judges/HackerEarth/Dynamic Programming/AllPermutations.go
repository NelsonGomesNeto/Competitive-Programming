package main

import "fmt"

/*
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
*/
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

func CopyArray(a []int) []int {
	a_copy := make([]int, len(a))
	copy(a_copy, a)
	return a_copy
}

func Has(all [][]int, a []int) bool {
	for _, e := range all {
		match := true
		for i := 0; i < len(a); i++ {
			if e[i] != a[i] {
				match = false
				break
			}
		}
		if match {
			return true
		}
	}
	return false
}

func main() {
	a := make([]int, 4)
	for i := range a {
		a[i] = i + 1
	}
	all_permutations := [][]int{}
	all_permutations = append(all_permutations, CopyArray(a))
	for NextPermutation(a) {
		if Has(all_permutations, a) {
			fmt.Println("failed")
			break
		}
		all_permutations = append(all_permutations, CopyArray(a))
	}
	for _, e := range all_permutations {
		fmt.Println(e)
	}
}
