# CSS-Parser

This project implements a simple **CSS processing engine**. It reads **CSS rules** and **command sections** from standard input. The CSS sections are parsed and stored in appropriate data structures. The project was created for university purposes.

## Project Description

### **CSS Parsing:**

- The processing begins by reading **CSS declarations**. The CSS is syntactically correct and consists of attribute blocks, optionally preceded by selectors. A lack of selectors is valid (it would mean that attributes apply to everything).
  
- **Selectors** are separated by commas. Legal CSS selectors are accepted, and it's assumed that they don’t contain commas or curly braces.

- Each block of attributes is enclosed in curly braces `{}`.

- **Attributes** are separated by semicolons and consist of a property name and a value, separated by a colon. The last attribute in a block may or may not be followed by a semicolon.

- Attribute values may be valid CSS constructs, but it's assumed that any strings will not contain malicious content such as escaped quotes, curly braces, or semicolons.

- If a specific attribute appears more than once in a block, it’s treated as a single occurrence, with the last value being significant.

- **Selectors, property names, and values** are treated as-is (after trimming leading and trailing whitespace), meaning no semantic interpretation is needed. For example, `"margin-left: 8px"` and `"margin: 4px 7px 4px 7px"` are treated as separate attributes with the names `margin-left` and `margin`, and values `8px` and `4px 7px 4px 7px` respectively.

- **Simplifications**:
  - No comments are present in the CSS.
  - No `@` selectors.
  - Blocks cannot be nested.

- **For testing purposes**, it's assumed that no selector or attribute spans multiple lines (although multiple separators and attributes can appear on the same line).

### **Commands:**

Commands are described in the format `???`, followed by actions for processing the CSS. These commands use integers `i` and `j` (positive integers) and `n` (a valid attribute name). Some possible commands include:

- **`****`**: Resume reading CSS.
- **`?`**: Output the number of CSS blocks.
- **`i,S,?`**: Output the number of selectors for block `i`. If block `i` doesn't exist, skip.
- **`i,A,?`**: Output the number of attributes for block `i`. If block `i` doesn't exist, skip.
- **`i,S,j`**: Output the `j`-th selector for block `i`. Skip if no such block or selector exists.
- **`i,A,n`**: Output the value of attribute `n` for block `i`. Skip if no such block or attribute exists.
- **`n,A,?`**: Output the total number of occurrences of attribute `n` across all blocks.
- **`z,S,?`**: Output the total number of occurrences of selector `z` across all blocks.
- **`z,E,n`**: Output the value of attribute `n` for selector `z`. If multiple occurrences exist, use the last one. Skip if none.
- **`i,D,*`**: Delete block `i` entirely. If successful, print `deleted`.
- **`i,D,n`**: Delete attribute `n` from block `i`. If the block is empty after the operation, it should be deleted as well. If successful, print `deleted`.

### **Implementation Notes:**

- **Selectors** and **attributes** are stored as lists.
- **CSS blocks** are organized as a doubly linked list (to efficiently handle the `E` command – retrieving the last occurrence of an attribute).
- To optimize memory usage, a node in the list should include an array `T` of size 8 representing a block. The count of used structures should help in speeding up operations.
- When allocating a new node, an array of `T` elements is created. If there's space in a node, new elements should be added to it before allocating a new node.
- If deleting elements leaves a node empty, the node should be removed.

### Example:

#### **Input:**

```css
????
?
1,S,?
1,S,1
1,A,?
2,A,font-family
h1,S,?
color,A,?
h1,E,color
1,A,padding
1,D,*
?
2,D,color
?

****
h1, h2, h3, h4, h5, h6 {color: #0066FF;}
????
?
```
#### **Output:**

```css
? == 3
1,S,? == 1
1,S,1 == #breadcrumb
1,A,? == 2
2,A,font-family == "Trebuchet MS", "Lucida Grande", Arial
h1,S,? == 2
color,A,? == 2
h1,E,color == #0066CB
1,D,* == deleted
? == 2
2,D, color == deleted
? == 1
? == 2
```
