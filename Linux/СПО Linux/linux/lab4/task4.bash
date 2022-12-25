#!/bin/bash

diff -rq $1/ $2/
diff <(du -sh $1) <(du -sh $2)

