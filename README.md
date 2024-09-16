# PIC-1D
A one-dimensional electrostatic particle-in-cell simulation code written in C++
# 0. Gaussian units and plasma equations
## 0.1 Maxwell equations

$$\nabla\times\vec{E}=-\frac{1}{c}\frac{\partial \vec{B}}{\partial t},~~ \nabla \times\vec{B}=\frac{4\pi}{c}\vec{j}+\frac{1}{c}\frac{\partial\vec{E}}{\partial t},~~ \nabla\cdot\vec{E}=4\pi\rho_e,~~ \nabla\cdot\vec{B}=0$$

$$F_{\rm Lorentz}=q\left(\vec{E}+\frac{\vec{x}\times\vec{B}}{c}\right)$$

## 0.2 Plasma equations

Debye length: $$\lambda_{De}=\sqrt{\frac{T_e}{4\pi n_0e^2}}$$, plasma period: $$\tau_{pe}=\frac{1}{\omega_{pe}}=\sqrt{\frac{m_e}{4\pi n_0 e^2}}$$

## 0.3 Constants
$$c=29979245800{\rm cm/s}$$

$$e=4.8032\times10^{-10}{\rm g^{1/2}cm^{3/2}s^{-1}}$$

$$m_e=9.10938215\times10^{-28}{\rm g}$$

$$m_p=1.672621637\times10^{-24}{\rm g}$$

## 0.4 Plasma units

Mass in unit of $m_e$, length in unit of $\lambda_{De}$, time in unit of $\tau_{pe}$. Suppose $\lambda_{De}=\lambda~{\rm cm},\tau_{pe}=\tau~{\rm s},m_e=m~{\rm g}$. 

$$v=\hat{v}[{\rm cm/s}] = \hat{v}\frac{\rm cm}{\lambda_{De}}\frac{\tau_{pe}}{\rm s}[\lambda_{De}/\tau_{pe}]=\left(\hat{v}\frac{\tau}{\lambda}\right)[\lambda_{De}/\tau_{pe}]$$

Thermal velocity is $$v_{\rm th}  = \sqrt{\frac{2T_e}{m_e}}=\sqrt{2}[{\rm \lambda_{De}/\tau_{pe}}]$$

$$c=\hat{c}[{\rm cm/s}]=\left(\hat{c}\frac{cm}{\lambda_{De}}\frac{\tau_{pe}}{s}\right)[{\rm \lambda_{De}/\tau_{pe}}]=\left(\hat{c}\frac{\tau}{\lambda}\right)[{\rm \lambda_{De}/\tau_{pe}}]$$

$$e=\hat{e}[{\rm g^{1/2}cm^{3/2}s^{-1}}]=\hat{e}\left(\frac{\rm g}{m_e}\right)^{1/2}\left(\frac{\rm cm}{\lambda_{De}}\right)^{3/2}\left(\frac{\tau_{pe}}{\rm s}\right)[{\rm {m_e^{1/2}}{\lambda_{De}^{3/2}}{\tau_{pe}^{-1}}}]=\left(\frac{\hat{e}\tau}{\sqrt{m\lambda^3}}\right)[{\rm {m_e^{1/2}}{\lambda_{De}^{3/2}}{\tau_{pe}^{-1}}}]$$

$$m_e = 1[{\rm m_e}]$$

$$m_p = \frac{m_p}{m_e} [{\rm m_e}]$$

# 1. Basic equations
Low index $i$ denotes number nodes and low index $p$ denotes number of particles. The number of nodes is $N_x$.
## 1.1 Gather
Suppose we have a field $E(\vec{x})$, and represent it as $E_i,i=0,1,2\cdots N_x-1$. For $p-th$ particle, its position is $x_p$, then

$$j={\rm int}\left(\frac{x_p-x_0}{dx}\right),~~~\Delta x=\frac{x_p-x_j}{dx},~~~E_p=(1-\Delta x)E_i+\Delta xE_{i+1}$$

## 1.2 Scatter
Suppose we konw the position of a particle. We need to scatter the quantity of particle to surrounding nodes.

$$j={\rm int}\left(\frac{x_p-x_0}{dx}\right),~~~\Delta x=\frac{x_p-x_j}{dx},~~~E_i=(1-\Delta x)E_p,E_{i+1}=\Delta xE_p$$

## 1.3 Finite Difference Method
Possion equation is $\nabla^2\phi=-4\pi\rho$, which means

$$\frac{\phi_{i+1}+\phi_{i-1}-2\phi_i}{dx^2}=-4\pi\rho_i$$

$$\phi_i = \frac{1}{2}(\phi_{i+1}+\phi_{i-1}+4\pi\rho_idx^2)$$

For periodic boundary conditions, 

$$\phi_0=\phi_{Nx-1},~\phi_{Nx-1}=\frac{1}{2}(\phi_{Nx-2}+\phi_1+4\pi\rho_{Nx-1}dx^2)$$

Now we have the potential, we can calculate the electric field, $$E=-\frac{\partial\phi}{\partial x}$$.

$$E_i=-\frac{\phi_{i+1}-\phi_{i-1}}{2dx},~~~ E_0=\frac{\phi_2-4\phi_1+3\phi_0}{2dx},~~~ E_{Nx-1}=-\frac{\phi_{Nx-3}-4\phi_{Nx-2}+3\phi_{Nx-1}}{2dx}$$

## 1.4 Leap frog method
The position of particles are in integer time step, and the velocity of particles are in half-integer time step.

$$v_p^{i+1/2}=v_p^{i-1/2}+\frac{qE_p^i}{m}dt,~~~ x_p^{i+1}=x_p^i+v_p^{i+1/2}dt$$

## 1.5 Linear equations
C++ library Eigen: https://eigen.tuxfamily.org/dox/GettingStarted.html

$$\begin{matrix}
&\phi_{Nx-1}-2\phi_0+\phi_{1}=-4\pi\rho_0dx^2\\
&\phi_{i-1}-2\phi_i+\phi_{i+1}=-4\pi\rho_idx^2\\
&\phi_{Nx-2}-2\phi_{Nx-1}+\phi_{1}=-4\pi\rho_{Nx-1}dx^2
\end{matrix}\Rightarrow \begin{matrix}
&\phi_{Nx-2}-2\phi_0+\phi_{1}=-4\pi\rho_0dx^2\\
&\phi_{Nx-1}-2\phi_1+\phi_2=-4\pi\rho_1dx^2\\
&\phi_{i-1}-2\phi_i+\phi_{i+1}=-4\pi\rho_idx^2\\
&\phi_{Nx-3}-2\phi_{Nx-2}+\phi_0=-4\pi\rho_{Nx-2}dx^2\\
&\phi_{Nx-2}-2\phi_{Nx-1}+\phi_{0}=-4\pi\rho_{Nx-1}dx^2
\end{matrix}\Rightarrow A\cdot\vec{\phi}=\vec{b}$$

$$A=
\begin{pmatrix}
&-2,&1,&0,&0,&\cdots,&0,&0,&1\\
&1,&-2,&1,&0,&\cdots,&0,&0,&0\\
&0,&1,&-2,&1,&\cdots,&0,&0,&0\\
&\cdots\\
&0,&0,&0,&0,&\cdots,&1,&-2,&1\\
&1,&0,&0,&0,&\cdots,&0,&1,&-2
\end{pmatrix},b=-4\pi dx^2\begin{pmatrix}
\rho_0\\
\rho_1\\
\rho_2\\
\cdots\\
\rho_{Nx-2}\\
\rho_{Nx-1}
\end{pmatrix}
$$

We cannot use LDLT decomposition method if $A$ is asymmetric.
