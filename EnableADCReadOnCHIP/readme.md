### Go to the  terminal global commands directory 

```bash
cd /bin
```
### Copy the scripts

```bash
wget https://raw.githubusercontent.com/thedub2001/tools/master/EnableADCReadOnCHIP/adcEnable
wget https://raw.githubusercontent.com/thedub2001/tools/master/EnableADCReadOnCHIP/adcRead
wget https://raw.githubusercontent.com/thedub2001/tools/master/EnableADCReadOnCHIP/adcReset
```
### Initiate ADC on pin 1V8 

```bash
adcEnable
```
### Read ADC value
The super user mode is needed by i2c-tools to read ADC 
```bash
su
adcRead
```

### Add adcEnable to startup
Because the CHIP initialize the 1V8 pin when booting we need to initialize it back in ADC mode
Edit the cron file
```bash
crontab -e
```
Add this line at the end of the file
```bash
@reboot adcEnable
```
