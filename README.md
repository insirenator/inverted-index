## Inverted Index implementation in C

An inverted index is a data structure used to store occurances of keywords found in a large corpus to make searching fast.
This is a crude implementation of an inverted index. A corpus in the form of a text file is read line by line and each word is stored in a hashtable in the form `line_number:word_position:char_position`:

```
"horse" -> ['1:3:18', '4:8:34']
...so on
```

Storing the information allows us to query the data effectively.
