#! /usr/bin/env bash
# vim: tabstop=4 shiftwidth=4 noexpandtab

# Use the local XXD
XXD="./xxd"

# Color output
RED='\e[31m'
GREEN='\e[32m'
RESET='\e[0m'

# Check that the output of running xxd on the test file is correct
cat >./test.tmp << EOV
00000000: b94191c12547b46778181546e839f495    .A..%G.gx..F.9..
00000010: ed5014c99d306c2742d3f12c2e4d47c9    .P...0l'B..,.MG.
00000020: 3339e7152ebf17658063b17e82eaf852    39.....e.c.~...R
00000030: f6a2ec90bfa4bd98fb11c41fe6f83b20    ..............;.
00000040: 4eba251e7d5b78a57cbbe614b14edcc8    N.%.}[x.|....N..
00000050: f21a9478a8c1f8eb9aecddf8ff44a410    ...x.........D..
00000060: 23bf8353bba43cb94f2d4d89329c204a    #..S..<.O-M.2..J
00000070: 990b7821826f0ca8b66389f69d6e3a47    ..x!.o...c...n:G
00000080: 4d44650885b5450b565bc3497b390f64    MDe...E.V[.I{9.d
00000090: dffc1b2e186f454355ef9b65fd82fd2c    .....oECU..e...,
000000a0: 84a4fb32241caec2d4d47cd34304f789    ...2$.....|.C...
000000b0: 2d22da4d8b22fc511cf6ab74d5f21c47    -".M.".Q...t...G
000000c0: 4cb6b6b5a13653be682c4b0c51173bcb    L....6S.h,K.Q.;.
000000d0: 27d271b8e77233cb02fd2d483b511ce3    '.q..r3...-H;Q..
000000e0: 1ed92f3012a0a966110367ac5661f212    ../0...f..g.Va..
000000f0: 0e3fa176520b373934e49fa14fe11c9e    .?.vR.794...O...

EOV

$XXD test.dat >./test.actual.tmp

git diff --no-index --word-diff=color --word-diff-regex=. test.tmp test.actual.tmp
STATUS="${?}"
if [[ "${STATUS}" != "0" ]]; then
	echo -e "[${RED}TEST FAILED${RESET}] XXD failed to produce expected output when run on test file" >&2
	rm ./*.tmp
else
	echo -e "[${GREEN}TEST PASSED${RESET}] Test data file"
fi

# Check that the help message shows
cat > 'test.tmp' <<EOV
XXD clone in C, by Connor Findlay
Version 1.6
Accepts a single filename as an argument, and has no flags
except -h for this text, and -v for the current version.
A single hyphen '-' indicates that standard input should be
read instead of a file
EOV

$XXD -h >'./test.actual.tmp'

git diff --no-index --word-diff=color --word-diff-regex=. test.tmp test.actual.tmp
STATUS="${?}"
if [[ "${STATUS}" != "0" ]]; then
	echo -e "[${RED}TEST FAILED${RESET}] XXD failed to produce correct help text" >&2
	rm ./*.tmp
else
	echo -e "[${GREEN}TEST PASSED${RESET}] Help flag"
fi

# Test the version flag
cat >'./test.tmp' << EOV
./xxd, version 1.60
EOV

$XXD -v >'./test.actual.tmp'
git diff --no-index --word-diff=color --word-diff-regex=. test.tmp test.actual.tmp
STATUS="${?}"
if [[ "${STATUS}" != "0" ]]; then
	echo -e "[${RED}TEST FAILED${RESET}] XXD failed to produce correct version text" >&2
	rm ./*.tmp
else
	echo -e "[${GREEN}TEST PASSED${RESET}] Version flag"
fi

# Test the stdin flag
cat >./test.tmp << EOV
00000000: b94191c12547b46778181546e839f495    .A..%G.gx..F.9..
00000010: ed5014c99d306c2742d3f12c2e4d47c9    .P...0l'B..,.MG.
00000020: 3339e7152ebf17658063b17e82eaf852    39.....e.c.~...R
00000030: f6a2ec90bfa4bd98fb11c41fe6f83b20    ..............;.
00000040: 4eba251e7d5b78a57cbbe614b14edcc8    N.%.}[x.|....N..
00000050: f21a9478a8c1f8eb9aecddf8ff44a410    ...x.........D..
00000060: 23bf8353bba43cb94f2d4d89329c204a    #..S..<.O-M.2..J
00000070: 990b7821826f0ca8b66389f69d6e3a47    ..x!.o...c...n:G
00000080: 4d44650885b5450b565bc3497b390f64    MDe...E.V[.I{9.d
00000090: dffc1b2e186f454355ef9b65fd82fd2c    .....oECU..e...,
000000a0: 84a4fb32241caec2d4d47cd34304f789    ...2$.....|.C...
000000b0: 2d22da4d8b22fc511cf6ab74d5f21c47    -".M.".Q...t...G
000000c0: 4cb6b6b5a13653be682c4b0c51173bcb    L....6S.h,K.Q.;.
000000d0: 27d271b8e77233cb02fd2d483b511ce3    '.q..r3...-H;Q..
000000e0: 1ed92f3012a0a966110367ac5661f212    ../0...f..g.Va..
000000f0: 0e3fa176520b373934e49fa14fe11c9e    .?.vR.794...O...

EOV

cat test.dat | xxd - >./test.actual.tmp
git diff --no-index --word-diff=color --word-diff-regex=. test.tmp test.actual.tmp
STATUS="${?}"
if [[ "${STATUS}" != "0" ]]; then
	echo -e "[${RED}TEST FAILED${RESET}] XXD failed to produce correct data when run on stdin" >&2
	rm ./*.tmp
else
	echo -e "[${GREEN}TEST PASSED${RESET}] Stdin flag"
fi
# Cleanup
rm -f ./*.tmp
