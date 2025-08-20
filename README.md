## AES ECB/CBC Random encryption
This is the random encryption of plaintext. the steps for encryption are used in this method
1) The Random bytes(5-10) are added before and after the plain text
2) The encryption key is randomly generated.
3) The mode of encryption is also Randomly choosen
4) If the mode of encryption is CBC, the IV will also choosen randomly.
The command to run this method is 
```./ecb-cbc-detect.sh ```
because of two initial random padding of random length, it is hard to detect ECB or CBC(for small plaintext).