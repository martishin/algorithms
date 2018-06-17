#!/usr/bin/env python3

from logic_circuits import *

g1 = AndGate('G1')
g2 = AndGate('G2')
g3 = NorGate('G3')
c1 = Connector(g1, g3)
c2 = Connector(g2, g3)
print(g3.getOutput())

g1 = NandGate('G1')
g2 = NandGate('G2')
g3 = AndGate('G3')
c1 = Connector(g1, g3)
c2 = Connector(g2, g3)
print(g3.getOutput())

