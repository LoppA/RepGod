import os
import sys
import json

class srcFile:
  def __init__(self, src, ex) :
    self.src = src
    self.ex = ex
    self.compile()
    self.wr = []

  def compile(self):
    cmd = "g++ " + self.src + " -O2 -o " + self.ex
    print(cmd)
    os.system(cmd)

  def run(self, case, out, flags=""):
    cmd = "./" + self.ex + " <" + case + " >" + out + " " + flags
    os.system(cmd)

  def report(self):
    if(len(self.wr) == 0):
      print(self.src + " OK!")
    else:
      print(self.src + " Wrong cases("+ str(len(self.wr))+ "): ", end="")
      for c in self.wr:
        print(c, end=" ")
      print()

if len(sys.argv) < 3:
  exit(0)
PMAX = int(sys.argv[1])
N = int(sys.argv[2])

with open("files.json") as json_file:
  data = json.load(json_file)

sol = []
for i in range (len(data["solution"])):
  src = srcFile(data["solution"][i], "Test/sol" + str(i))
  sol.append(src)
brute = srcFile(data["brute"], "Test/brute")
gen = srcFile(data["generator"], "Test/gen")

for i in range(N):
  case = "Test/case" + str(i)
  cmd = "./" + gen.ex + " >" + case + " " + str(PMAX)
  os.system(cmd)
  
  brute.run(case, "Test/brute.out", str(PMAX))

  print("Case " , i);

  for s in sol:
    s.run(case, "Test/sol.out")
    if(os.system("diff Test/brute.out Test/sol.out") != 0):
      s.wr.append(i)

for s in sol:
  s.report()
