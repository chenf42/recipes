//package main

// import (
// 	"fmt"
// 	"log"
// 	"net/http"
// )

// type Hello struct {}

// func (h Hello) ServeHTTP(
// 	w http.ResponseWriter,
// 	r *http.Request) {
// 	fmt.Fprint(w, "Hello, world!")
// }

// func main() {
// 	var h Hello
// 	err := http.ListenAndServe("localhost:4000", h)
// 	if err != nil {
// 		log.Fatal(err)
// 	}
// }

package main

import (
	"fmt"
	"log"
	"net/http"
)

type String string

type Struct struct {
	Greeting string
	Punct string
	Who string
}

func (s String) ServeHTTP(
	w http.ResponseWriter,
	r *http.Request) {
	fmt.Fprint(w, s)
}

func (s Struct) ServeHTTP(
	w http.ResponseWriter,
	r *http.Request) {
	fmt.Fprintf(w, "%s%s%s", s.Greeting, s.Punct, s.Who)
}

func main() {
	http.Handle("/string", String("I'm a frayed knot."))
	http.Handle("/struct", &Struct{"Hello", ":", "Gophers!"})

	log.Fatal(http.ListenAndServe("localhost:4000", nil))
}

