# Test file for Lab4_StateMachines


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Test sequence from waitA0: A0, !A0, A1 => PORTB: 1
test "state: lock, PINA 0x04, PINA 0x02  => state: unlocked"
set state = lock
setPINA 0x04
continue
setPINA 0x02
continue
expect state unlock
checkResult

test "state: unlocked, PINA 0x80  => state: locked"
set state = unlock
setPINA 0x80
continue
expect state lock
checkResult

test "PINA: 0x04 => state : wait"
set state = lock
setPINA 0x04
continue
expect state wait
checkResult

test "PINA: 0x04,0x01 => state: locked"
set state = lock
setPINA 0x04
continue
setPINA 0x01
continue
expect state lock
checkResult

test "state: lock, PINA 0x04, PINA 0x02  => state: unlocked, state: locked"
set state = lock
setPINA 0x04
continue
setPINA 0x02
continue
expect state unlock
setPINA 0x04
continue
setPINA 0x02
continue
expect state lock
checkResult


# Add tests below

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
