# 规范

## `namespace G`下的继承关系
1. 一切类（纯虚类除外）继承自`G::Object`
2. 如果不是final类需要使用虚继承
3. 派生类的某一父类继承自`G::Object`，该类不用声明继承`G::Object`
