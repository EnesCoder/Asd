#!/bin/zsh

set -e # stop on errors

make
sudo cp -r asd /usr/bin/asd
# git
git add .
git commit -m $1
git push
