#!/bin/bash
g++ detection_oracle.cpp process.cpp randreq.cpp ecb_enc_dec.cpp -o out
./out
