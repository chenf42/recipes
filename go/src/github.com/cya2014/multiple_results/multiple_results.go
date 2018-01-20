package main

import "fmt"

// 参数类型一致，可将前面的类型省略掉
// 但返回值就不行了，得写全

// func reverse(x, y, z string) (string, string, string) {
func reverse(x, y, z string) (a, b, c string) {  // 不过如果给返回值命名，就又可以这样做了
	//return z, y, x  // 给返回值命名的情况下，可以按原来这样写，也可以像下面这样使用“裸”返回
	a = z
	b = y
	c = x
	return
}

func main() {
	a, b, c := reverse("hello", "world", "bye")
	fmt.Println(a, b, c)
}
