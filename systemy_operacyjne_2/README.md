## Command chaining

* `command1 &` - run in background
* `command1 ; command2` - run two commands sequentially
* `command1 && command2` - run sequentially, preceding must succeed
* `command1 || command2` - run second if first fail
* `command1 | command2` - pipe; output of first command act as input of second

### Command combination '{}'
```
$ [ -d bin ] || { echo Directory does not exist, creating directory now.; mkdir bin; } && echo Directory exists.
```

### "if/else"
```
$ ping -c3 www.tecmint.com && echo "Verified" || echo "Host Down"
```