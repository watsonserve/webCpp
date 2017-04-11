#!/bin/python
#coding=utf-8

import os

# 区分C++ 和 C
def makeout(src_file):
    obj_file = '$(OBJ)/' + src_file.replace('/', '_').replace('.', '_') + '.o'

    if src_file.endswith('cpp'):
        a_relation = '$(CXX) $(CXXFLAGS)'
    elif src_file.endswith('c'):
        a_relation = '$(CC) $(CFLAGS)'

    return [obj_file, '%s : $(SRC)/%s\n\t%s $^ -o $@ -I $(INC)\n' % (obj_file, src_file, a_relation)]


def main():

    # 创建存放目标文件的目录
    if not os.path.exists(OBJ_DIR):
        os.makedirs(OBJ_DIR)
    if not os.path.exists(LIB_DIR):
        os.makedirs(LIB_DIR)

    # 编译framework
    aoRelations = dict()
    osRelations = dict()
    share_dep = dict()

    for parent, dirnames, filenames in os.walk(framework):
        if parent == framework:
            for dirname in dirnames:
                aFile = '$(LIB)/lib' + dirname.capitalize() + '.a'
                aoRelations[aFile] = []
                osRelations[aFile] = []

            for filename in filenames:
                osr = makeout(os.path.join('framework', filename))
                share_dep[osr[0]] = osr[1]
        else:

            # 分开一级目录和子目录
            dirname = parent[1 + len(framework):].split('/', 1)
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

    so += '\n'

    for aLib in aoRelations:
        so += '%s : %s\n\t$(AR) $(ARFLAGS) $@ $^\n\n%s\n\n' % (aLib, ' '.join(aoRelations[aLib]), '\n'.join(osRelations[aLib]))

    fd = open('makefile', 'w+')
    fd.write('%s\n\n%s\n' % ('\n'.join(header), so))
    fd.close()

if '__main__' == __name__:
    header = [
        '#! /bin/make',
        'ROOT = %s' % (os.path.split(os.path.realpath(__file__))[0]),
        'OBJ = /tmp/.objs',
        'SRC = $(ROOT)/src',
        'ASM = /tmp/.asms',
        'INC = $(ROOT)/include',
        'LIB = $(ROOT)/lib',
        'BIN = $(ROOT)/bin',
        'CXX = g++',
        'CC = gcc',
        'AR = ar',
        'AS = as',
        'LD = ld',
        'CFLAGS = -c -O3 -Wall',
        'CXXFLAGS = -c -O3 -Wall --std=c++11',
        'ARFLAGS = -crsv',
        'SHAREFLAGS = -shared -fPIC -lc -lrt -lpthread -lstdc++'
    ]
    LIB_DIR = 'lib'
    OBJ_DIR = '/tmp/.objs'
    framework = 'src/framework'

    main()
