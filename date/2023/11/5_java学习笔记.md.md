# 路漫漫其修远兮，吾将上下而求索

## 一、有效编程

- 重写equals方法必须实现等价关系
  - **自反性**(reflexive)
  - **对称性**(symmetric)
  - **传递性**(transitive)
  - **一致性**(consistent)

- 在每个覆盖equals方法的类中也必须覆盖HashCode方法
  - 不覆写违反了Object.hashCode的通用约定，从而导致该类无法结合散列的集合一起正常运作，这样的集合包括HashMap、HashSet和Hashtable
  
