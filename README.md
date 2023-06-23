# physics
#Tasks to code 

### To compile and run from console:  
Go to ==src== folder and write:  
'''  
g++ [evdokimova_project.cpp] -o [project] -I /usr/include/python3.8/ -I include/ -lpython3.8  
./project  
'''  


##Task: [diffraction grid](https://github.com/DaryaEvd/physics/tree/main/difraction_grid).  
To compile and run:  
g++ evdokimova_diff_grid.cpp -o grid -I /usr/include/python3.8/ -I include/ -lpython3.8  
./grid   
or  
use cmake:   
from 'build' folder write:  
cmake ..  
make  
./diffraction_grid  

Result:  
![plot](https://github.com/DaryaEvd/physics/blob/main/difraction_grid/Figure_1_diff_grid.png)  
  
Task: [potential hole](https://github.com/DaryaEvd/physics/tree/main/potential_hole).  
To compile and run:  
g++ evdokimova_solutions.cpp -o solutions -I /usr/include/python3.8/ -I include/ -lpython3.8  
./solutions [width of hole]  
g++ evdokimova_levels.cpp -o levels -I /usr/include/python3.8/ -I include/ -lpython3.8   
./levels [width of hole]   
   
or use cmake:  
cmake ..  
make  
./solutions [width of hole]  
or  
./levels [width of hole]  

Result:  
Solutions:  
![plot](https://github.com/DaryaEvd/physics/blob/main/potential_hole/Figure_4.png)  
  
Levels:  
![plot](https://github.com/DaryaEvd/physics/blob/main/potential_hole/Figure_5_levels.png)    



