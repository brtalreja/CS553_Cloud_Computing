#!/bin/bash

TEST_REPO_URL="https://github.com/datasys-classrooms/cs553-fall2022-hw3-testing.git"
TEST_REPO_DIR="cs553-fall2022-hw3-testing"

if [ ! -d $TEST_REPO_DIR ]
then
    git clone $TEST_REPO_URL
fi

cd $TEST_REPO_DIR
git fetch & git pull
cd ..

cp $TEST_REPO_DIR/test-data-single.txt test-data-single.txt
cp $TEST_REPO_DIR/test-data-double.txt test-data-double.txt

bash $TEST_REPO_DIR/check-submission.sh all
bash $TEST_REPO_DIR/test-submission.sh all
