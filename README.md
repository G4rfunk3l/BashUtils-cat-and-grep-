# BashUtils (cat, grep)
My own realization of cat and grep for Mac and Linux (C Language). 
For build do make all, then for using type ./my_cat or ./my_grep and parameters like below.
For tests do make test.
## Realized features
### cat usage:
cat [OPTION] [FILE]... (like default cat)
### cat flags:
#### -n (GNU: --number)
Number all output lines
#### -b (GNU: --number-nonblank)
Numbers only non-empty lines
#### -e implies -v
Use ^ and M- notation, except for LFD and TAB and show all nonprinting, -e see below
#### GNU only: -E the same as -e, but without implying -v
display end-of-line characters as $
#### -s (GNU: --squeeze-blank)
squeeze multiple adjacent blank lines
#### -t implies -v (GNU: -T the same, but without implying -v)
display tabs as ^I
### grep usage:
grep [options] template [file_name] (like default grep)
### grep flags:
#### -e
Pattern
#### -i
Ignore uppercase vs. lowercase
#### -v
Invert match
#### -c
Output count of matching lines only
#### -l
Output matching files only
#### -n
Precede each matching line with a line number
#### -h
Output matching lines without preceding them by file names
#### -s
Suppress error messages about nonexistent or unreadable files
#### -f file
Take regexes from a file
#### -o
Output the matched parts of a matching line

