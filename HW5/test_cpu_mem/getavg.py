from audioop import avg
from typing import List
 
class TxtHandler(object):
 
    def __init__(self, filepath):
        self.filepath = filepath
 
    def writer(self, content):
        with open(self.filepath, "w+") as f:
            f.write(content)
 
    def reader(self):
        with open(self.filepath, "r") as f:
            return f.read()
 
 
class GetLines(object):
 
    def txt(self, way: str) -> str:
        return TxtHandler(way).reader()
 
    def enter_cut(self, txt: str) -> List[str]:
        return [line for line in  txt.splitlines() if "# " != line[0:2]]
 
    def get_msg(self, sentence_list: List[str]) -> List[int]:
        cpu = []
        mem = []
        for sentence in sentence_list:
            l = sentence.split(" ")
            i = 0
            for s in l:
                if s == "":
                    continue
                if i == 1:
                    cpu.append(float(s))
                if i == 2:
                    mem.append(float(s))
                    break
                i+=1

        return cpu, mem

        
 
if __name__ == "__main__":
    way = r"linuxsort16.txt"
    lines = GetLines()
    content = lines.txt(way)
    lines_list = lines.enter_cut(content)
    cpu, mem = lines.get_msg(lines_list)
    # print(cpu)
    print(sum(cpu) / len(cpu))
    print(sum(mem) / len(mem))