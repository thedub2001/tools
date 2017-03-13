###   Open the .bashrc file located in your home directory or ~ directory
``` nano .bashrc ```
###  Add your function at the end of the .bashrc file
```bash
date1(){
  date -d @$1
}
```
###  Export your function to make it available to super user
Write this code at the end of the .bashrc file
```
export -f date1
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
### Test your new function in super user mode
```bash
su -c date1 123456
```
