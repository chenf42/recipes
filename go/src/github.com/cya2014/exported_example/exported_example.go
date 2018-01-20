package main

import "github.com/cya2014/exported"

func main() {
	exported.Return1()
	// exported.return2()  // 只有首字母大写的被导出了，小写不导出
}