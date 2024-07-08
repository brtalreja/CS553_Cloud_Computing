#!/bin/bash

TEST_REPO_URL="https://github.com/datasys-classrooms/cs553-fall2022-hw5-testing.git"
TEST_REPO_DIR="cs553-fall2022-hw5-testing"

if [ ! -d $TEST_REPO_DIR ]
then
    git clone $TEST_REPO_URL
fi

cd $TEST_REPO_DIR
git fetch & git pull
cd ..

bash $TEST_REPO_DIR/check-submission.sh all
bash $TEST_REPO_DIR/test-submission.sh all