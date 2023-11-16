/**
 * Author: Anton Mokrousov
 * Date: 2023-11-16
 * License: CC0
 * Source: CPP reference
 * Description: Better RNG than rand()
 * Status: tested
 */
#pragma once

random_device rd; mt19937_64 gen(rd());

int blessRng(ll a, ll b) {
	uniform_int_distribution<ll> rnd(a,b); return rnd(gen);
}