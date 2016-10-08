import numpy as np
import matplotlib.pyplot as plt 

with open('MOTOR_DATA_BWD.txt', "r") as f:
	content_bwd = f.readlines()
with open('MOTOR_DATA_FWD.txt', "r") as f:
	content_fwd = f.readlines()
content_bwd = [x.strip('\r\n') for x in content_bwd]
content_fwd = [x.strip('\r\n') for x in content_fwd]
print(content_bwd)
print(content_fwd)
PWM = []
M1 = []
M2 = []

for lines in content_bwd:
	if lines[0] == 'P':
		PWM += [int(s) for s in lines.split() if s.isdigit()]
	elif lines[0] == '#':
		M1 += [int(s) for s in lines.split() if s.isdigit()]
	elif lines[0] == '$':
		M2 += [int(s) for s in lines.split() if s.isdigit()]

# for lines in content_fwd:
# 	if lines[0] == 'P':
# 		PWM += [int(s) for s in lines.split() if s.isdigit()]
# 	elif lines[0] == '#':
# 		M1 += [int(s) for s in lines.split() if s.isdigit()]
# 	elif lines[0] == '$':
# 		M2 += [int(s) for s in lines.split() if s.isdigit()]
print(PWM)
print(M1)
print(M2)

plt.plot(PWM,M1)
plt.plot(PWM,M2)
plt.show()