@echo off
set input=7.txt
set output=7_dec.txt
openssl enc -d -aes-128-ecb -base64 -in %input% -out %output% -K 59454C4C4F57205355424D4152494E45