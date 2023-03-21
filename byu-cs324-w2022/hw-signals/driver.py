#!/usr/bin/python3

import argparse
import re
import subprocess
import sys
import time

NUM_TESTS = 10

KILL_RE = re.compile(r'^kill\(\d+, (SIG[A-Z0-9]+|\d+)\)')

class KillTest:
    signals = './signals'
    killer = './killer'
    
    scenario = None
    solution = None
    max_time = None
    disallowed_signals = ['SIGKILL', '9']

    def grade(self):
        cmd = ['strace', '-e', 'trace=%signal',
                self.signals, self.killer, str(self.scenario)]

        start_time = time.time()
        p = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        end_time = time.time()

        # Check output
        if self.solution is not None:
            expected = self.stringify_solution()
            actual = p.stdout.decode('utf-8').strip()
            if expected != actual:
                print(f'\nExpected:\n{expected}\n\nGot:\n{actual}\n')
                return False

        # Check timing
        if self.max_time is not None:
            time_elapsed = int(end_time - start_time)
            if time_elapsed > self.max_time:
                print(f'\nTime elapsed: {time_elapsed}s\nMaximum allowed: {self.max_time}s\n')
                return False

        # Check signals
        if self.disallowed_signals is not None:
            output = p.stderr.decode('utf-8').strip()
            for line in output.splitlines():
                m = KILL_RE.search(line)
                if m is None:
                    continue
                sig_used = m.group(1)
                if sig_used in self.disallowed_signals:
                    print(f'\n{sig_used} not allowed\n')
                    return False

        return True

    def stringify_solution(self):
        return '\n'.join([str(i) for i in self.solution])

class KillTest0(KillTest):
    scenario = 0
    solution = [1, 2, 25]
    
class KillTest1(KillTest):
    scenario = 1
    solution = []
    
class KillTest2(KillTest):
    scenario = 2
    solution = [1, 2]
    
class KillTest3(KillTest):
    scenario = 3
    solution = [1, 2, 1, 2]
    
class KillTest4(KillTest):
    scenario = 4
    solution = [1, 1, 2, 2]
    
class KillTest5(KillTest):
    scenario = 5
    solution = [1]
    
class KillTest6(KillTest):
    scenario = 6
    solution = [1, 2, 7, 10]
    
class KillTest7(KillTest):
    scenario = 7
    solution = [1, 2, 7]
    
class KillTest8(KillTest):
    scenario = 8
    solution = [1, 2, 6]
    
class KillTest9(KillTest):
    scenario = 9
    solution = [8, 9, 1, 2]
    disallowed_signals = ['SIGHUP', 'SIGINT', '1', '2']
    

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('scenario', action='store',
            nargs='?', type=int, choices=range(NUM_TESTS))
    args = parser.parse_args(sys.argv[1:])
    
    thismodule = sys.modules[__name__]
    if args.scenario is None:
        score = 0
        max_score = 0
        for scenario in range(NUM_TESTS):
            sys.stdout.write(f'Testing scenario {scenario}:')
            sys.stdout.flush()
            max_score += 1
            cls = getattr(thismodule, f'KillTest{scenario}', None)
            test = cls()
            if test.grade():
                sys.stdout.write('   PASSED\n')
                sys.stdout.flush()
                score += 1
            else:
                sys.stdout.write('   FAILED\n')
                sys.stdout.flush()
        print(f'Score: {score}/{max_score}')
    else:
        scenario = args.scenario
        sys.stdout.write(f'Testing scenario {scenario}:')
        sys.stdout.flush()
        cls = getattr(thismodule, f'KillTest{scenario}', None)
        test = cls()
        if test.grade():
            sys.stdout.write('   PASSED\n')
            sys.stdout.flush()
        else:
            sys.stdout.write('   FAILED\n')
            sys.stdout.flush()

if __name__ == '__main__':
    main()
