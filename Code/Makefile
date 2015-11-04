# GNU make手册：http://www.gnu.org/software/make/manual/make.html
# ************ 遇到不明白的地方请google以及阅读手册 *************

# 编译器设定和编译选项
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -std=c99

# 编译目标：src目录下的所有.c文件
CFILES = $(shell find ./ -name "*.c")
OBJS = $(CFILES:.c=.o)
LFILE = $(shell find ./ -name "*.l")
YFILE = $(shell find ./ -name "*.y")
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)
YFC = $(shell find ./ -name "*.y" | sed s/[^/]*\\.y/syntax.tab.c/)
LFO = $(LFC:.c=.o)
YFO = $(YFC:.c=.o)

parser: syntax $(filter-out $(LFO),$(OBJS))
	$(CC) -g -o parser $(filter-out $(LFO),$(OBJS)) -lfl -ly 

syntax: lexical syntax-c
	$(CC) -g -c $(YFC) -o $(YFO)

lexical: $(LFILE)
	$(FLEX)  -o $(LFC) $(LFILE)

syntax-c: $(YFILE)
	$(BISON) -o $(YFC) -d -v -t $(YFILE)

-include $(patsubst %.o, %.d, $(OBJS))

# 定义的一些伪目标
.PHONY: clean SDDtest debug
SDDtest:
	./parser ../Test/SDDtest/test1.cmm
	./parser ../Test/SDDtest/test2.cmm
	./parser ../Test/SDDtest/test3.cmm
	./parser ../Test/SDDtest/test4.cmm
	./parser ../Test/SDDtest/test5.cmm
	./parser ../Test/SDDtest/test6.cmm
	./parser ../Test/SDDtest/test7.cmm
	./parser ../Test/SDDtest/test8.cmm
	./parser ../Test/SDDtest/test9.cmm
	./parser ../Test/SDDtest/test10.cmm
	./parser ../Test/SDDtest/test11.cmm
	./parser ../Test/SDDtest/test12.cmm
	./parser ../Test/SDDtest/test13.cmm
	./parser ../Test/SDDtest/test14.cmm
	./parser ../Test/SDDtest/test15.cmm
	./parser ../Test/SDDtest/test16.cmm
	./parser ../Test/SDDtest/test17.cmm
clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f *~
debug:
	gcc -g -o parser main.c syntax.tab.c parser.c nTree.c SDD/SDD.c Symbol/*.c -lfl -ly
	gdb parser
