# physics

## [Tasks to code](https://github.com/DaryaEvd/physics/blob/main/stuff/tasks.pdf)  

### To compile and run from console:  
Go to `src` folder in any project and write from there:  
```
g++ [evdokimova_project.cpp] -o [project] -I /usr/include/python3.8/ -I include/ -lpython3.8  
./project  
```

## Task: [DIFFRACTION GRID](https://github.com/DaryaEvd/physics/tree/main/difraction_grid)  
### To compile and run use Cmake:  
Go to `build` folder and write from there: 
``` 
cmake ..  
make  
./[diffraction_grid]  
```  

#### Result:  
![viewOfGrid](https://github.com/DaryaEvd/physics/blob/main/difraction_grid/pictures/Diffraction_grid.png  )  
  
## Task: [POTENTIAL HOLE](https://github.com/DaryaEvd/physics/tree/main/potential_hole)   

### To compile and run use Cmake:  
Go to `build` folder and write from there: 
``` 
cmake ..  
make
./[solutions] [width of hole]  
or
./[levels] [width of hole]  
or  
./[waves] [width of hole]    
```  

#### Result:  
##### Solutions:  
![solutions](https://github.com/DaryaEvd/physics/blob/main/potential_hole/pictures/Solutions.png)  

  
##### Levels:  
![symmetric](https://github.com/DaryaEvd/physics/blob/main/potential_hole/pictures/Symmetric_levels.png)  
![assymetric](https://github.com/DaryaEvd/physics/blob/main/potential_hole/pictures/Assymmetric_levels.png)  

##### Waves:
###### For width 10
![symmetric](https://github.com/DaryaEvd/physics/blob/main/potential_hole/pictures/Symetric_waves_10.png) 
 
![assymetric](https://github.com/DaryaEvd/physics/blob/main/potential_hole/pictures/Assymetric_waves_10.png)  

###### For width 20
![symmetric](https://github.com/DaryaEvd/physics/blob/main/potential_hole/pictures/Symetric_waves_20.png) 
![assymetric](https://github.com/DaryaEvd/physics/blob/main/potential_hole/pictures/Assymetric_waves_20.png)  

## Task [TIME DEPENDENT SCHRODINGER EQUATION](https://github.com/DaryaEvd/physics/tree/main/wave_time)  

### To compile and run use Cmake:  
Go to `build` folder and write from there: 
```
cmake ..  
make  
./equation [time]  
```  
Result:  
![tdse](https://github.com/DaryaEvd/physics/blob/main/wave_time/pictures/TDSE_1.png)  


### Some recommendations about using matplotlibcpp  
1. There **always** should be at least one `plt::plot(...)` method in `main`.  
2. Use `plt::title()` only **after** `plt::plot(...)`.  
Otherwise `seg fault` is guaranted ((  





