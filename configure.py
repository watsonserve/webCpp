#!/bin/python
#coding=utf-8

import os
from sys import platform

# 区分C++ 和 C
def makeout(src_file):
    obj_file = '$(OBJ)/' + src_file.replace('/', '_').replace('.', '_') + '.o'
    a_relation = 'exit(1)\n'

    if src_file.endswith('cpp'):
        a_relation = '$(CXX) $(CXXFLAGS)'
    elif src_file.endswith('c'):
        a_relation = '$(CC) $(CFLAGS)'

    return [obj_file, '%s : $(SRC)/%s\n\t%s $^ -o $@ -I $(INC)\n' % (obj_file, src_file, a_relation)]

class Makefile:
    def __init__(self, prefix = '', dirTree = {}):
        self.framework = 'src/framework'
        self.root = os.path.split(os.path.realpath(__file__))[0]
        self.prefix = prefix
        self.dirTree = dirTree

    def header(self):
        shareflags = 'SHAREFLAGS = -shared -fPIC -lc -lpthread -lstdc++'
        if 'darwin' != platform:
            shareflags += ' -lrt'

        return '\n'.join([
            '#! /bin/make',
            'PREFIX = %s' % self.prefix,
            'ROOT = %s' % self.root,
            'INC = $(ROOT)/include',
            'SRC = $(ROOT)/src',
            'DIST = $(ROOT)/dist',
            'OBJ = $(DIST)/objs',
            'ASM = $(DIST)/asms',
            'LIB = $(DIST)/lib',
            'BIN = $(DIST)/bin',
            'CXX = g++',
            'CC = gcc',
            'AR = ar',
            'AS = as',
            'LD = ld',
            'CFLAGS = -c -O3 -Wall',
            'CXXFLAGS = -c -O3 -Wall --std=c++11',
            'ARFLAGS = -crsv',
            shareflags,
            '\n'
        ])

    def target(self):
        # 编译framework
        aoRelations = dict()
        osRelations = dict()
        share_dep = dict()

        for parent, dirnames, filenames in os.walk(self.framework):
            if parent == self.framework:
                for dirname in dirnames:
                    aFile = '$(LIB)/lib' + dirname.capitalize() + '.a'
                    aoRelations[aFile] = []
                    osRelations[aFile] = []

                for filename in filenames:
                    osr = makeout(os.path.join('framework', filename))
                    share_dep[osr[0]] = osr[1]
            else:

                # 分开一级目录和子目录
                dirname = parent[1 + len(self.framework):].split('/', 1)
                aName = dirname[0]
                aFile = '$(LIB)/lib' + aName.capitalize() + '.a'
                for filename in filenames:
                    srcFile = os.path.join('framework', aName, '_'.join(dirname[1:]), filename)

                    # 加入静态库依赖队列
                    osr = makeout(srcFile)
                    aoRelations[aFile].append(osr[0])
                    osRelations[aFile].append(osr[1])

        so = '$(LIB)/libFramework.so : %s\n\t$(CXX) $(SHAREFLAGS) -o $@ $^\n\n\n' % (' '.join(aoRelations))
        # for dep in share_dep:
        #     so += share_dep[dep] + '\n'
        for aLib in aoRelations:
            so += '%s : %s\n\t$(AR) $(ARFLAGS) $@ $^\n\n%s\n\n' % (aLib, ' '.join(aoRelations[aLib]), '\n'.join(osRelations[aLib]))
        return so
    
    def install(self):
        return '\n'.join([
            'install :',
            '\tmv $(LIB)/*.a %s/lib/' % self.prefix,
            '\tmv $(LIB)/*.so %s/lib/' % self.prefix,
            '\n',
        ])

    def clean(self):
        foo = map(lambda word: '\trm -rf $(DIST)/' + word.name, self.dirTree.childs)
        return '\n'.join(['clean :'] + foo + ['\n'])

    def __str__(self):
        return '\n'.join([self.header(), self.target(), self.clean(), self.install()])

# 中序遍历目录树，创建目录
def makedirs(dirTree, path = ''):
    if '' != path:
        path += '/'

    absPath = path + dirTree.name

    if not os.path.exists(absPath):
        os.makedirs(absPath)

    for item in dirTree.childs:
        makedirs(item, absPath)

class DirTreeNode:
    def __init__(self, name = ''):
        self.childs = []
        self.name = name

    def addChild(self, name = ''):
        childNode = DirTreeNode(name)
        self.childs.append(childNode)

def main():
    distDir = DirTreeNode('dist')
    distDir.addChild('objs')
    distDir.addChild('asms')
    distDir.addChild('lib')

    makefile = Makefile('', distDir)

    # 创建存放目标文件的目录
    makedirs(distDir)

    fd = open('makefile', 'w+')
    fd.write('%s' % makefile)
    fd.close()

if '__main__' == __name__:
    main()
