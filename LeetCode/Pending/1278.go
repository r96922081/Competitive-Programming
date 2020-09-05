package main

import (
	"fmt"
)

func check(b bool) {
	if !b {
		fmt.Println("failed!!!")
	}
}

func diff(s string, l, r, length int) int {
	if l != r && r-l != 1 {
		return -1
	}

	l2 := l
	r2 := r

	diff_count := 0

	for i := 0; i < length; i++ {
		if l2 < 0 {
			return -1
		}
		if r2 >= len(s) {
			return -1
		}

		if s[l2] != s[r2] {
			diff_count++
		}
		l2--
		r2++
	}

	return diff_count
}

func diff1(s string) int {
	r := len(s) / 2
	l := r
	if len(s)%2 == 0 {
		l = r - 1
	}

	length := (len(s) + 1) / 2

	return diff(s, l, r, length)
}

func diff2(s string, partition []int) int {

	strings := []string{}

	left := 0

	if len(partition) == 0 {
		strings = append(strings, s)
	} else {
		for i := 0; i < len(partition); i++ {
			strings = append(strings, s[left:partition[i]])
			left = partition[i]
		}

		strings = append(strings, s[partition[len(partition)-1]:])
	}

	diff_count := 0
	for i := 0; i < len(strings); i++ {
		s2 := strings[i]
		r := len(s2) / 2
		l := r
		if len(s2)%2 == 0 {
			l = r - 1
		}

		diff_count += diff(s2, l, r, (len(s2)+1)/2)
	}

	return diff_count
}

func bruteForce2(s string, k int, k_index int, partition []int) int {
	if len(partition) == k {
		return diff2(s, partition)
	}

	if k_index == len(s) {
		return 10000
	}

	if k_index == 0 {
		return bruteForce2(s, k, 1, partition)
	}

	addedIndex := len(partition)
	partition = append(partition, k_index)
	value1 := bruteForce2(s, k, k_index+1, partition)
	partition = append(partition[:addedIndex], partition[addedIndex+1:]...)

	value2 := bruteForce2(s, k, k_index+1, partition)

	if value1 < value2 {
		return value1
	}

	return value2
}

func bruteForce(s string, k int) int {
	partition := []int{}
	return bruteForce2(s, k-1, 0, partition)
}

func dp_solution2(s string, l int, r int, k int, dp_table [][][]int) int {
	if dp_table[l][r][k] != -1 {
		return dp_table[l][r][k]
	}

	if k == 1 {
		dp_table[l][r][1] = diff1(s[l:r])
		return dp_table[l][r][1]
	}

	minDiff := 100
	for i := 1; i <= r-l-1; i++ {
		for j := 1; j <= k-1; j++ {
			diff_left := dp_solution2(s, l, l+i, j, dp_table)
			diff_right := dp_solution2(s, l+i, r, k-j, dp_table)
			if diff_left+diff_right < minDiff {
				minDiff = diff_left + diff_right
			}
		}
	}

	dp_table[l][r][k] = minDiff
	return minDiff
}

// TLE
func dp_solution(s string, k int) int {
	dp_table := make([][][]int, len(s)+1)
	for i := 0; i < len(s)+1; i++ {
		dp_table[i] = make([][]int, len(s)+1)
		for j := 0; j < len(s)+1; j++ {
			dp_table[i][j] = make([]int, len(s)+1)
			for k := 0; k < len(s)+1; k++ {
				dp_table[i][j][k] = -1
			}
		}
	}

	return dp_solution2(s, 0, len(s), k, dp_table)
}

func greedy_solution(s string, k int) int {
	if k == 1 {
		value := diff1(s)
		return value
	}

	min := 200
	separator := -1

	for i := 1; i < len(s); i++ {
		left := diff1(s[:i])
		right := diff1(s[i:])

		if left+right < min {
			min = left + right
			separator = i
		}
	}

	min = 200
	for i := 1; i <= k-1; i++ {
		left_str := s[:separator]
		right_str := s[separator:]

		if i > len(left_str) || k-i > len(right_str) {
			continue
		}

		left := greedy_solution(s[:separator], i)
		right := greedy_solution(s[separator:], k-i)

		if left+right < min {
			min = left + right
		}
	}

	return min
}

func palindromePartition(s string, k int) int {
	return 0
}

func testAgainstBruteForce2(s string, str_len int, str_index int) {
	if str_index == str_len {
		s2 := s[:str_len]
		for k := 1; k <= str_len; k++ {
			check(bruteForce(s2, k) == dp_solution(s2, k))
		}

		return
	}

	for i := 0; i < str_len; i++ {
		out := []rune(s)
		out[str_index] = rune('a' + byte(i))
		s = string(out)
		testAgainstBruteForce2(s, str_len, str_index+1)
	}
}

func testAgainstBruteForce() {
	s := ""
	for i := 0; i < 100; i++ {
		s += " "
	}

	for str_len := 1; str_len <= 5; str_len++ {
		testAgainstBruteForce2(s, str_len, 0)
	}
}

func main() {
	check(diff("a", -1, 0, 1) == -1)
	check(diff("a", 0, 1, 1) == -1)
	check(diff("a", 0, 0, 0) == 0)
	check(diff("a", 0, 0, 1) == 0)
	check(diff("ab", 0, 1, 1) == 1)
	check(diff("aa", 0, 1, 1) == 0)
	check(diff("abcd", 1, 2, 1) == 1)
	check(diff("abcd", 1, 2, 2) == 2)
	check(diff("abca", 1, 2, 2) == 1)
	check(diff("abcde", 2, 2, 1) == 0)
	check(diff("abcde", 2, 2, 2) == 1)
	check(diff("abcde", 2, 2, 3) == 2)
	check(diff("abcba", 2, 2, 2) == 0)
	check(diff("abcba", 2, 2, 3) == 0)

	testAgainstBruteForce()

	/*
		check(diff2("abcde", []int{}) == 2)
		check(diff2("abcde", []int{1, 4}) == 1)
		check(diff2("abcee", []int{1, 3}) == 1)
		check(diff2("abcba", []int{}) == 0)
		check(diff2("abbc", []int{1, 3}) == 0)
		check(diff2("abdc", []int{1, 3}) == 1)

		fmt.Println(palindromePartition("leetcode", 8))

		//check(palindromePartition("abc", 2) == 1)
		//check(palindromePartition("aabbc", 3) == 0)
		//check(palindromePartition("leetcode", 8) == 0)
	*/
}
