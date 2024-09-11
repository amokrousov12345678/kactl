/**
 * Author: Somebody
 * Date: Somewhen
 * License: CC0
 * Source: based on KACTL's FFT
 * Description: $B_1 = 1/a_0$, $B_{2k} = B_k(2-AB_k)$ (trunc to $2k$)
 * $A_nB_n = 1 (mod x^n)$, so $B=A^{-1}$. $A/B = AB^{-1} (mod x^n)$
 * Time: O(N \log N)
 * Status: unknown
 */