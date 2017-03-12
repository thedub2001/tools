###   Open the .bashrc file located in your home directory or ~ directory
``` nano .bashrc ```
###  Add your function at the end of the .bashrc file
```bash
date1(){
  date -d @$1
}
```
### Save your file
```
Ctrl+X
```

### Actualize the function just created
```bash
source ~/.bashrc
```
### Test your new function
```bash
date1 132456
```
