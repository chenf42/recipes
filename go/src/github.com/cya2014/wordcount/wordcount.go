package wc

import (
	"strings"
)

func Wordcount(s string) map[string]int {
	r := make(map[string]int)
	words := strings.Fields(s)
	for _, word := range words {
		r[word]++
	}
	return r
}
