# physics
Tasks to code 

Task: [diffraction grid](https://github.com/DaryaEvd/physics/tree/main/difraction_grid).  
To compile and run:  
g++ evdokimova_diff_grid.cpp -o grid -I /usr/include/python3.8/ -I include/ -lpython3.8  
./grid   
or  
use cmake:   
from 'build' folder write:  
cmake ..  
make  

Result:  
![plot](https://github.com/DaryaEvd/physics/blob/main/difraction_grid/Figure_1_diff_grid.png)  
  
Task: [potential hole](https://github.com/DaryaEvd/physics/tree/main/potential_hole).  
To compile and run:  
g++ evdokimova_potential_hole.cpp -o hole -I /usr/include/python3.8/ -I include/ -lpython3.8  
./hole [width of hole]  
Result:
Huge scale:  
![plot](https://github.com/DaryaEvd/physics/blob/main/potential_hole/Figure_2.png)  
  
OK scale:  
![plot](https://github.com/DaryaEvd/physics/blob/main/potential_hole/Figure_4.png)  


