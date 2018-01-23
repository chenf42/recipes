package main

import (
	"fmt"
	"math"
)

type Point struct {
	X, Y float64
}

func (p Point) DistToOrigin() float64 {
	return math.Sqrt(math.Pow(p.X, 2) + math.Pow(p.Y, 2))
}

// 根据 https://tour.go-zh.org/methods/3 处的叙述，此版本（使用指针作为 method 的接收者）
// 更好，因为可以避免在每个方法调用中去拷贝 Point 的值
func (p *Point) DistToOrigin2() float64 {
	return math.Sqrt(math.Pow(p.X, 2) + math.Pow(p.Y, 2))
}

// 不能给基础类型添加 method
// 编译报错： cannot define methods on non-local type float64
// func (f float64) MyAbs() float64 {
// 	if f < 0 {
// 		return -f
// 	}
// 	return f
// }

type MyFloat float64

func (f MyFloat) MyAbs() MyFloat {
	if f < 0 {
		return -f
	}
	return f
}

func main() {
	p := Point{1, 1}
	fmt.Println(p.DistToOrigin())
	fmt.Println((&p).DistToOrigin2())

	x := MyFloat(-1.0)
	fmt.Println(x.MyAbs())
}
