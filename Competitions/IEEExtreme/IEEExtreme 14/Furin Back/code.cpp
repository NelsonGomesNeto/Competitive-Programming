#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

char hehe[5];

string brainfuck = " \
                                      >,>,>,<[->-                \
                                   >+<<]>>[-<<+>>]             \
                                 <<<[->-<<+>]<           \
                                [->+<]>>>>>>+>>>>          \
                               >>>+[>>>>[-]<[-]<[-         \
                              ]<         [-]<[+        \
                             --]<<             <<<<<       \
                            <<                 <<<[->      \
                           >>>>>>+                     >>>>>     \
                          >+<<<            <          <<<<<    \
                         <<<<]>[           ->>           >>>   \
                        >>+>>          >>>>+            <<<<<  \
                       <<<<<           <<<]>             [->>>>> \
                                         >>+                     \
                                         >>>>-                     \
                                         +>>                     \
                                         +<<<<                     \
                                         <<<                     \
          <<<<<<        ]     >>+>+[<-]      <[->>     \
       +<<<]>>>>      [-<<<     <<<<+>>>>      >>>]>     \
      [-<<<<<<<+>     >>>     >>>]>[-<<<<<<      <+>     \
     >>>>>>]>>>>>>>+    [-<<<     <<<<<<<      <[->>     \
    +>>+<<<<]>[->>+>>   +<<     <<]>[-<<+>>]>[-      <<+>>     \
   ]+[[-]+>[<-]<[   -     >>-<<<]>>->      >>+>[     \
  <-]<[-       >+>[-    <-]<[          >>[-<           <->     \
  ]-<<[->         -     >>-          <<<           <]]<]     \
  >>-<<<           <      <+>[>          <<-]<           [>>     \
 [<<-                   >]<<[          <]]>-           ]>>     \
 >>>>                   >>+          ]-<<<           <     \
 +>-                    ++[<-          ]<[           >>+[<     \
 <->                    ]<<          [>>>+           [<<     \
 <->>]                    <<<[<          ]]]>-           ]>>>>     \
 [-]<<                    <<<<<          <           <<<<<     \
 <[-]>                    >+>+[          <-]<[           ->>+<     \
 <<]                    >+>[<          -]<[>           >[<<-     \
 >]<<[                    <]]>-          [+>>>           >>>     \
 +++                    +++++          ++<<<           <<<+>     \
 [<                   -]<[>          >[<<-           >]<<[     \
 <]]>-[                   ++>[<          -]<[-           >>-<<     \
  <]>>->           >      +>>+>          -[<-]           <[<<[     \
  ->>>+<<         <     ]>>          >>>+>           +[<     \
  -]<[->       >+<<<    ]<<-<          ]<<<<           +>[<-     \
   ]<[>>[<<->]<<[<]]>-]   >>+++          +++++[   ->     +++++     \
    +<]>[-<<<<+>>>>]>>>   >>+          >[<-]<[>>     [<<->     \
     ]<<[<]]>-[++>[<-]    <[->>          -<<<]>>-<<<     <<<<<     \
      +>+[<-]<[->>+<<     <]>>>          >>>>>+>[<-      ]<[>>     \
       [<<->]<<[<]]>      -]<<[           -]<<<<<+>      [<-]<     \
          [>>[<<->        ]<<[<            ]]>-]<<       [.<]!     \
";

int tape[10000], ptr, inptr;
stack<int> lol;
void run2(string &code, int i = 0, int rec = 0)
{
  int open = 0;
  while (i < code.size())
  {
    // printf("%04d (%02d) - %c | %02d | %02d | %04d\n", i, rec, code[i], ptr, inptr, tape[ptr]);
    switch (code[i])
    {
      case '>':
        ptr++;
        break;

      case '<':
        ptr--;
        break;

      case '+':
        tape[ptr]++;
        if (tape[ptr] > 126)
          tape[ptr] = 0;
        break;

      case '-':
        tape[ptr]--;
        if (tape[ptr] < 0)
          tape[ptr] = 126;
        break;

      case '[':
        lol.push(i);
        if (tape[ptr] == 0)
        {
          // if (outer > i)
          //   i = outer;

          // int open = 1;
          // while (open)
          // {
          //   i++;
          //   if (code[i] == '[') open++;
          //   else if (code[i] == ']') open--;
          // }
          lol.pop();
          return;
        }

        break;

      case ']':
        if (tape[ptr] != 0)
        {
          int prv = lol.top();
          lol.pop();
          run2(brainfuck, prv, rec + 1);
        }
        else
          lol.pop();
        break;

      // case '[':
      //   while (tape[ptr] != 0)
      //     run2(code, i + 1, rec + 1);
      //   open = 1;
      //   while (open)
      //   {
      //     i++;
      //     if (code[i] == '[') open++;
      //     else if (code[i] == ']') open--;
      //   }

      //   break;

      // case ']':
      //   return;
      //   break;

      case ',':
        tape[ptr] = hehe[inptr++];
        break;

      case '.':
        putchar(tape[ptr]);
        break;

      default:
        break;
    }

    i++;
  }
}

void run3()
{
  int ptr = 0;
int tape[10000]; memset(tape, '\0', sizeof(tape));
ptr += 1;
tape[ptr] = hehe[inptr++];
ptr -= 1;
ptr += 1;
ptr += 1;
tape[ptr] = hehe[inptr++];
ptr += 1;
tape[ptr] = hehe[inptr++];
ptr -= 1;
while (tape[ptr] != 0) {
    tape[ptr] -= 1;
    ptr += 1;
    tape[ptr] -= 1;
    ptr += 1;
    tape[ptr] += 1;
    ptr -= 1;
    ptr += 1;
    ptr -= 1;
    ptr -= 1;
    }
tape[ptr] += 1;
tape[ptr] -= 1;
ptr += 1;
ptr += 1;
while (tape[ptr] != 0) {
    tape[ptr] -= 1;
    ptr -= 1;
    ptr -= 1;
    tape[ptr] += 1;
    ptr += 1;
    ptr += 1;
    }
ptr -= 1;
tape[ptr] += 1;
tape[ptr] -= 1;
ptr += 1;
ptr -= 1;
ptr += 1;
ptr -= 1;
ptr -= 1;
ptr -= 1;
while (tape[ptr] != 0) {
    tape[ptr] -= 1;
    tape[ptr] += 1;
    tape[ptr] -= 1;
    ptr += 1;
    tape[ptr] -= 1;
    ptr -= 1;
    tape[ptr] += 1;
    tape[ptr] -= 1;
    ptr -= 1;
    tape[ptr] += 1;
    ptr += 1;
    }
ptr -= 1;
while (tape[ptr] != 0) {
    tape[ptr] -= 1;
    ptr += 1;
    tape[ptr] += 1;
    ptr -= 1;
    }
ptr += 1;
ptr -= 1;
ptr += 1;
ptr += 1;
ptr += 1;
ptr += 1;
ptr += 1;
ptr += 1;
ptr -= 1;
ptr += 1;
tape[ptr] += 1;
tape[ptr] += 1;
tape[ptr] -= 1;
ptr += 1;
ptr += 1;
tape[ptr] += 1;
tape[ptr] -= 1;
ptr += 1;
ptr += 1;
ptr += 1;
ptr += 1;
ptr += 1;
tape[ptr] += 1;
while (tape[ptr] != 0) {
    ptr += 1;
    ptr += 1;
    ptr -= 1;
    ptr += 1;
    ptr += 1;
    ptr += 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        }
    ptr -= 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        ptr -= 1;
        ptr += 1;
        tape[ptr] -= 1;
        tape[ptr] += 1;
        }
    ptr -= 1;
    ptr -= 1;
    ptr += 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        tape[ptr] += 1;
        tape[ptr] -= 1;
        }
    tape[ptr] -= 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] -= 1;
    tape[ptr] += 1;
    tape[ptr] -= 1;
    ptr -= 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        }
    ptr -= 1;
    ptr += 1;
    ptr -= 1;
    ptr -= 1;
    ptr += 1;
    while (tape[ptr] != 0) {
        tape[ptr] += 1;
        tape[ptr] -= 1;
        tape[ptr] -= 1;
        tape[ptr] -= 1;
        tape[ptr] += 1;
        }
    ptr -= 1;
    ptr += 1;
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    tape[ptr] += 1;
    tape[ptr] -= 1;
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    ptr += 1;
    tape[ptr] -= 1;
    tape[ptr] += 1;
    ptr -= 1;
    ptr += 1;
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    ptr += 1;
    ptr -= 1;
    tape[ptr] += 1;
    tape[ptr] -= 1;
    ptr -= 1;
    ptr -= 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        tape[ptr] += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        tape[ptr] -= 1;
        tape[ptr] += 1;
        ptr += 1;
        tape[ptr] += 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr += 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr += 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        }
    ptr += 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr -= 1;
        ptr += 1;
        ptr -= 1;
        ptr += 1;
        ptr += 1;
        ptr -= 1;
        ptr += 1;
        ptr += 1;
        tape[ptr] += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        tape[ptr] += 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr += 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        tape[ptr] += 1;
        tape[ptr] -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        }
    ptr += 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr -= 1;
        ptr += 1;
        tape[ptr] += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        tape[ptr] -= 1;
        tape[ptr] += 1;
        ptr += 1;
        ptr -= 1;
        ptr += 1;
        ptr += 1;
        tape[ptr] += 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        tape[ptr] += 1;
        tape[ptr] -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr += 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        tape[ptr] -= 1;
        tape[ptr] += 1;
        ptr += 1;
        ptr -= 1;
        }
    ptr += 1;
    ptr += 1;
    tape[ptr] -= 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] -= 1;
    tape[ptr] += 1;
    ptr += 1;
    tape[ptr] += 1;
    tape[ptr] -= 1;
    tape[ptr] += 1;
    while (tape[ptr] != 0) {
        ptr -= 1;
        tape[ptr] -= 1;
        }
    ptr -= 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        ptr += 1;
        ptr += 1;
        ptr -= 1;
        ptr += 1;
        tape[ptr] += 1;
        tape[ptr] += 1;
        tape[ptr] -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        }
    ptr += 1;
    ptr += 1;
    ptr += 1;
    ptr += 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        tape[ptr] += 1;
        tape[ptr] -= 1;
        tape[ptr] -= 1;
        tape[ptr] += 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        tape[ptr] += 1;
        ptr += 1;
        ptr += 1;
        ptr -= 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        }
    ptr += 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        ptr -= 1;
        ptr -= 1;
        tape[ptr] -= 1;
        tape[ptr] += 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        tape[ptr] += 1;
        ptr -= 1;
        ptr += 1;
        ptr += 1;
        tape[ptr] += 1;
        tape[ptr] -= 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        }
    ptr += 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr += 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr += 1;
        ptr -= 1;
        ptr -= 1;
        tape[ptr] += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        }
    ptr += 1;
    ptr += 1;
    ptr += 1;
    ptr += 1;
    ptr += 1;
    ptr += 1;
    ptr -= 1;
    ptr += 1;
    ptr += 1;
    tape[ptr] += 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        tape[ptr] += 1;
        tape[ptr] -= 1;
        tape[ptr] -= 1;
        tape[ptr] += 1;
        ptr -= 1;
        ptr += 1;
        ptr -= 1;
        tape[ptr] += 1;
        tape[ptr] -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        while (tape[ptr] != 0) {
            tape[ptr] -= 1;
            ptr += 1;
            ptr += 1;
            tape[ptr] += 1;
            ptr += 1;
            ptr += 1;
            tape[ptr] += 1;
            ptr -= 1;
            ptr -= 1;
            ptr -= 1;
            ptr -= 1;
            }
        tape[ptr] += 1;
        tape[ptr] -= 1;
        ptr += 1;
        while (tape[ptr] != 0) {
            tape[ptr] -= 1;
            ptr += 1;
            ptr += 1;
            tape[ptr] += 1;
            ptr += 1;
            ptr += 1;
            tape[ptr] += 1;
            tape[ptr] -= 1;
            tape[ptr] += 1;
            ptr -= 1;
            ptr -= 1;
            ptr -= 1;
            ptr -= 1;
            }
        ptr += 1;
        while (tape[ptr] != 0) {
            tape[ptr] -= 1;
            ptr -= 1;
            ptr -= 1;
            tape[ptr] += 1;
            ptr += 1;
            ptr += 1;
            }
        ptr += 1;
        while (tape[ptr] != 0) {
            tape[ptr] -= 1;
            ptr -= 1;
            ptr -= 1;
            tape[ptr] += 1;
            ptr += 1;
            ptr += 1;
            }
        tape[ptr] += 1;
        while (tape[ptr] != 0) {
            while (tape[ptr] != 0) {
                ptr -= 1;
                ptr += 1;
                tape[ptr] -= 1;
                }
            tape[ptr] -= 1;
            tape[ptr] += 1;
            tape[ptr] += 1;
            ptr += 1;
            while (tape[ptr] != 0) {
                ptr -= 1;
                tape[ptr] -= 1;
                }
            ptr -= 1;
            tape[ptr] += 1;
            tape[ptr] -= 1;
            while (tape[ptr] != 0) {
                tape[ptr] += 1;
                tape[ptr] -= 1;
                tape[ptr] -= 1;
                ptr += 1;
                ptr -= 1;
                ptr += 1;
                ptr += 1;
                ptr -= 1;
                ptr += 1;
                tape[ptr] -= 1;
                ptr -= 1;
                ptr -= 1;
                ptr -= 1;
                }
            ptr += 1;
            ptr += 1;
            tape[ptr] -= 1;
            tape[ptr] += 1;
            tape[ptr] -= 1;
            ptr += 1;
            ptr += 1;
            ptr += 1;
            tape[ptr] += 1;
            ptr += 1;
            while (tape[ptr] != 0) {
                ptr -= 1;
                tape[ptr] -= 1;
                }
            ptr -= 1;
            tape[ptr] += 1;
            tape[ptr] -= 1;
            while (tape[ptr] != 0) {
                tape[ptr] -= 1;
                ptr += 1;
                tape[ptr] += 1;
                ptr += 1;
                while (tape[ptr] != 0) {
                    tape[ptr] -= 1;
                    ptr -= 1;
                    tape[ptr] -= 1;
                    }
                ptr -= 1;
                while (tape[ptr] != 0) {
                    ptr += 1;
                    ptr += 1;
                    while (tape[ptr] != 0) {
                        tape[ptr] -= 1;
                        ptr -= 1;
                        ptr -= 1;
                        tape[ptr] -= 1;
                        tape[ptr] += 1;
                        tape[ptr] -= 1;
                        ptr += 1;
                        }
                    tape[ptr] -= 1;
                    ptr -= 1;
                    ptr -= 1;
                    while (tape[ptr] != 0) {
                        tape[ptr] -= 1;
                        ptr += 1;
                        ptr += 1;
                        ptr -= 1;
                        tape[ptr] -= 1;
                        ptr += 1;
                        tape[ptr] += 1;
                        tape[ptr] -= 1;
                        ptr += 1;
                        tape[ptr] -= 1;
                        tape[ptr] += 1;
                        tape[ptr] -= 1;
                        ptr -= 1;
                        ptr -= 1;
                        ptr -= 1;
                        ptr -= 1;
                        }
                    }
                ptr -= 1;
                }
            ptr += 1;
            ptr += 1;
            tape[ptr] -= 1;
            ptr -= 1;
            ptr -= 1;
            ptr -= 1;
            ptr -= 1;
            ptr -= 1;
            tape[ptr] += 1;
            ptr += 1;
            while (tape[ptr] != 0) {
                ptr += 1;
                ptr -= 1;
                ptr -= 1;
                tape[ptr] -= 1;
                }
            ptr -= 1;
            while (tape[ptr] != 0) {
                ptr += 1;
                tape[ptr] += 1;
                tape[ptr] -= 1;
                ptr += 1;
                while (tape[ptr] != 0) {
                    tape[ptr] -= 1;
                    tape[ptr] += 1;
                    ptr -= 1;
                    ptr -= 1;
                    tape[ptr] -= 1;
                    ptr += 1;
                    }
                ptr -= 1;
                ptr -= 1;
                while (tape[ptr] != 0) {
                    ptr -= 1;
                    }
                }
            ptr += 1;
            tape[ptr] -= 1;
            tape[ptr] += 1;
            tape[ptr] -= 1;
            }
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr -= 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr -= 1;
        ptr += 1;
        tape[ptr] += 1;
        }
    tape[ptr] -= 1;
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    ptr += 1;
    tape[ptr] += 1;
    tape[ptr] -= 1;
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    ptr += 1;
    tape[ptr] += 1;
    ptr += 1;
    tape[ptr] -= 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    while (tape[ptr] != 0) {
        ptr -= 1;
        tape[ptr] -= 1;
        }
    ptr -= 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        tape[ptr] += 1;
        ptr += 1;
        ptr += 1;
        tape[ptr] += 1;
        while (tape[ptr] != 0) {
            ptr -= 1;
            ptr -= 1;
            ptr -= 1;
            ptr += 1;
            tape[ptr] -= 1;
            ptr += 1;
            tape[ptr] -= 1;
            tape[ptr] += 1;
            }
        ptr -= 1;
        ptr -= 1;
        while (tape[ptr] != 0) {
            ptr += 1;
            ptr += 1;
            ptr += 1;
            tape[ptr] += 1;
            while (tape[ptr] != 0) {
                ptr -= 1;
                tape[ptr] -= 1;
                tape[ptr] += 1;
                ptr -= 1;
                ptr -= 1;
                tape[ptr] -= 1;
                ptr += 1;
                ptr += 1;
                }
            ptr -= 1;
            ptr -= 1;
            ptr -= 1;
            while (tape[ptr] != 0) {
                ptr -= 1;
                }
            }
        }
    ptr += 1;
    tape[ptr] -= 1;
    }
ptr += 1;
ptr += 1;
ptr += 1;
ptr += 1;
while (tape[ptr] != 0) {
    tape[ptr] -= 1;
    }
ptr -= 1;
ptr -= 1;
ptr -= 1;
ptr -= 1;
ptr -= 1;
ptr -= 1;
ptr -= 1;
tape[ptr] -= 1;
tape[ptr] += 1;
ptr -= 1;
ptr += 1;
ptr -= 1;
ptr -= 1;
ptr -= 1;
ptr -= 1;
ptr -= 1;
ptr -= 1;
ptr -= 1;
while (tape[ptr] != 0) {
    tape[ptr] -= 1;
    }
ptr += 1;
ptr += 1;
tape[ptr] += 1;
ptr += 1;
tape[ptr] += 1;
while (tape[ptr] != 0) {
    ptr -= 1;
    tape[ptr] -= 1;
    }
ptr -= 1;
while (tape[ptr] != 0) {
    tape[ptr] -= 1;
    ptr += 1;
    ptr += 1;
    tape[ptr] += 1;
    ptr -= 1;
    ptr += 1;
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    }
ptr += 1;
tape[ptr] += 1;
ptr += 1;
while (tape[ptr] != 0) {
    ptr -= 1;
    tape[ptr] -= 1;
    }
ptr -= 1;
while (tape[ptr] != 0) {
    ptr += 1;
    ptr += 1;
    while (tape[ptr] != 0) {
        ptr -= 1;
        ptr -= 1;
        tape[ptr] -= 1;
        ptr += 1;
        }
    ptr -= 1;
    ptr -= 1;
    while (tape[ptr] != 0) {
        ptr -= 1;
        }
    }
ptr += 1;
tape[ptr] -= 1;
while (tape[ptr] != 0) {
    tape[ptr] += 1;
    ptr += 1;
    ptr += 1;
    ptr += 1;
    ptr += 1;
    ptr += 1;
    ptr += 1;
    ptr += 1;
    ptr -= 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] -= 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    tape[ptr] += 1;
    ptr += 1;
    tape[ptr] += 1;
    tape[ptr] -= 1;
    while (tape[ptr] != 0) {
        ptr -= 1;
        ptr -= 1;
        ptr += 1;
        tape[ptr] -= 1;
        }
    ptr -= 1;
    while (tape[ptr] != 0) {
        ptr += 1;
        ptr += 1;
        while (tape[ptr] != 0) {
            ptr -= 1;
            ptr -= 1;
            tape[ptr] -= 1;
            ptr += 1;
            }
        ptr -= 1;
        ptr -= 1;
        while (tape[ptr] != 0) {
            ptr -= 1;
            }
        }
    ptr += 1;
    tape[ptr] -= 1;
    while (tape[ptr] != 0) {
        tape[ptr] += 1;
        tape[ptr] += 1;
        ptr += 1;
        while (tape[ptr] != 0) {
            ptr -= 1;
            tape[ptr] -= 1;
            }
        ptr -= 1;
        while (tape[ptr] != 0) {
            tape[ptr] -= 1;
            ptr += 1;
            ptr += 1;
            tape[ptr] -= 1;
            ptr -= 1;
            ptr -= 1;
            ptr -= 1;
            }
        ptr += 1;
        ptr += 1;
        tape[ptr] -= 1;
        ptr += 1;
        ptr += 1;
        tape[ptr] += 1;
        ptr += 1;
        ptr += 1;
        tape[ptr] += 1;
        ptr += 1;
        tape[ptr] -= 1;
        while (tape[ptr] != 0) {
            ptr -= 1;
            tape[ptr] -= 1;
            }
        ptr -= 1;
        while (tape[ptr] != 0) {
            ptr -= 1;
            ptr -= 1;
            while (tape[ptr] != 0) {
                tape[ptr] -= 1;
                ptr += 1;
                ptr += 1;
                ptr += 1;
                tape[ptr] += 1;
                ptr -= 1;
                ptr -= 1;
                ptr += 1;
                ptr -= 1;
                ptr -= 1;
                }
            tape[ptr] += 1;
            tape[ptr] -= 1;
            ptr += 1;
            ptr += 1;
            ptr += 1;
            ptr += 1;
            ptr += 1;
            tape[ptr] += 1;
            ptr += 1;
            tape[ptr] += 1;
            while (tape[ptr] != 0) {
                ptr -= 1;
                ptr += 1;
                ptr -= 1;
                tape[ptr] -= 1;
                }
            ptr -= 1;
            ptr += 1;
            ptr -= 1;
            while (tape[ptr] != 0) {
                tape[ptr] -= 1;
                ptr += 1;
                ptr += 1;
                tape[ptr] += 1;
                ptr -= 1;
                ptr -= 1;
                ptr -= 1;
                }
            ptr -= 1;
            ptr -= 1;
            tape[ptr] -= 1;
            ptr -= 1;
            }
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        tape[ptr] += 1;
        ptr += 1;
        while (tape[ptr] != 0) {
            ptr -= 1;
            tape[ptr] -= 1;
            }
        ptr -= 1;
        while (tape[ptr] != 0) {
            ptr += 1;
            ptr += 1;
            while (tape[ptr] != 0) {
                ptr -= 1;
                ptr -= 1;
                tape[ptr] -= 1;
                ptr += 1;
                }
            ptr -= 1;
            ptr -= 1;
            while (tape[ptr] != 0) {
                ptr -= 1;
                }
            }
        ptr += 1;
        tape[ptr] -= 1;
        }
    ptr += 1;
    ptr += 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    tape[ptr] += 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        ptr += 1;
        tape[ptr] += 1;
        tape[ptr] += 1;
        tape[ptr] += 1;
        tape[ptr] += 1;
        tape[ptr] += 1;
        tape[ptr] += 1;
        ptr -= 1;
        }
    ptr += 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        tape[ptr] += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        }
    ptr += 1;
    ptr += 1;
    ptr += 1;
    ptr += 1;
    ptr += 1;
    tape[ptr] += 1;
    ptr += 1;
    ptr -= 1;
    ptr += 1;
    tape[ptr] -= 1;
    tape[ptr] += 1;
    while (tape[ptr] != 0) {
        ptr -= 1;
        tape[ptr] -= 1;
        }
    ptr -= 1;
    while (tape[ptr] != 0) {
        ptr += 1;
        ptr += 1;
        while (tape[ptr] != 0) {
            ptr -= 1;
            ptr -= 1;
            tape[ptr] -= 1;
            ptr += 1;
            }
        ptr -= 1;
        ptr -= 1;
        while (tape[ptr] != 0) {
            ptr -= 1;
            }
        }
    ptr += 1;
    tape[ptr] -= 1;
    while (tape[ptr] != 0) {
        tape[ptr] += 1;
        tape[ptr] += 1;
        ptr += 1;
        while (tape[ptr] != 0) {
            ptr -= 1;
            tape[ptr] -= 1;
            }
        ptr -= 1;
        while (tape[ptr] != 0) {
            tape[ptr] -= 1;
            ptr += 1;
            ptr += 1;
            tape[ptr] -= 1;
            ptr -= 1;
            ptr -= 1;
            ptr -= 1;
            }
        ptr += 1;
        ptr += 1;
        tape[ptr] -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        ptr -= 1;
        tape[ptr] += 1;
        ptr += 1;
        tape[ptr] += 1;
        while (tape[ptr] != 0) {
            ptr -= 1;
            tape[ptr] -= 1;
            }
        ptr -= 1;
        while (tape[ptr] != 0) {
            tape[ptr] -= 1;
            ptr += 1;
            ptr += 1;
            tape[ptr] += 1;
            ptr -= 1;
            ptr -= 1;
            ptr -= 1;
            }
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        ptr += 1;
        tape[ptr] += 1;
        ptr += 1;
        while (tape[ptr] != 0) {
            ptr -= 1;
            tape[ptr] -= 1;
            }
        ptr -= 1;
        while (tape[ptr] != 0) {
            ptr += 1;
            ptr += 1;
            while (tape[ptr] != 0) {
                ptr -= 1;
                ptr -= 1;
                tape[ptr] -= 1;
                ptr += 1;
                }
            ptr -= 1;
            ptr -= 1;
            while (tape[ptr] != 0) {
                ptr -= 1;
                }
            }
        ptr += 1;
        tape[ptr] -= 1;
        }
    ptr -= 1;
    ptr -= 1;
    while (tape[ptr] != 0) {
        tape[ptr] -= 1;
        }
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    ptr -= 1;
    tape[ptr] += 1;
    ptr += 1;
    while (tape[ptr] != 0) {
        ptr -= 1;
        tape[ptr] -= 1;
        }
    ptr -= 1;
    while (tape[ptr] != 0) {
        ptr += 1;
        ptr += 1;
        while (tape[ptr] != 0) {
            ptr -= 1;
            ptr -= 1;
            tape[ptr] -= 1;
            ptr += 1;
            }
        ptr -= 1;
        ptr -= 1;
        while (tape[ptr] != 0) {
            ptr -= 1;
            }
        }
    ptr += 1;
    tape[ptr] -= 1;
    }
ptr -= 1;
ptr -= 1;
while (tape[ptr] != 0) {
    putchar(tape[ptr]);
    ptr -= 1;
    }


}

vector<pair<int, char>> onlyBrackets;
void run(string &code, int i = 0, int rec = 0)
{
  stack<int> loops; int outer = -1;
  while (i < code.size())
  {
    // printf("%04d (%02d) - %c | %02d | %02d | %04d\n", i, (int)loops.size(), code[i], ptr, inptr, tape[ptr]);
    switch (code[i])
    {
      case '>':
        ptr++;
        break;

      case '<':
        ptr--;
        break;

      case '+':
        tape[ptr]++;
        if (tape[ptr] > 255)
          tape[ptr] = 0;
        break;

      case '-':
        tape[ptr]--;
        if (tape[ptr] < 0)
          tape[ptr] = 255;
        break;

      case '[':
        loops.push(i);
        if (tape[ptr] == 0)
        {
          // if (outer > i)
          //   i = outer;
          int ii = lower_bound(onlyBrackets.begin(), onlyBrackets.end(), make_pair(i, '\0')) - onlyBrackets.begin();
          int open = 1;
          while (open)
          {
            ii++;
            if (onlyBrackets[ii].second == '[') open++;
            else if (onlyBrackets[ii].second == ']') open--;
          }
          i = onlyBrackets[ii].first;
          loops.pop();
        }

        break;

      case ']':
        if (tape[ptr] != 0)
          i = loops.top() - 1;
        loops.pop();
        break;

      case ',':
        tape[ptr] = hehe[inptr++];
        break;

      case '.':
        putchar(tape[ptr]);
        break;

      default:
        break;
    }

    i++;
  }
}

int main()
{
  string valids = "><[]+-,.";
  string aux = "";
  for (int i = 0; i < brainfuck.size(); i++)
  {
    bool valid = false;
    for (int j = 0; j < valids.size(); j++)
      if (brainfuck[i] == valids[j])  
        valid = true;
    aux += brainfuck[i];
  }
  brainfuck = aux;

  for (int i = 0; i < brainfuck.size(); i++)
    onlyBrackets.push_back({i, brainfuck[i]});

  int t;
  while (scanf("%d", &t) != EOF)
  {
    scanf(" %s", hehe);
    memset(tape, '\0', sizeof(tape));
    ptr = 0, inptr = 0;
    // run3();
    run(brainfuck);
    printf("\n");
  }
  return 0;
}