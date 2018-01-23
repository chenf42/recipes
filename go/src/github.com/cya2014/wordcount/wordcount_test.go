package wc

import (
	"testing"
	"reflect"
)

func TestWordcount(t *testing.T) {
	cases := []struct {
		in string
		want map[string]int
	} {
		{"hello world", map[string]int{"hello":1, "world":1}},
		{"hello world", map[string]int{"hello":1, "world":1}},
		{"1 2 3 1 1 3 3 3", map[string]int{"1":3, "2":1, "3":4}},
	}

	for _, c := range cases {
		got := Wordcount(c.in)
		if !reflect.DeepEqual(got, c.want) {
			t.Errorf("Wordcount(%q) == %q, want %q", c.in, got, c.want)
		}
	}
}
