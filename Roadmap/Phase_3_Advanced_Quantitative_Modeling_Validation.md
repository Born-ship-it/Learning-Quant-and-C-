
## Phase 3: Advanced Quantitative Modeling & Model Validation (Months 12–30)
*This phase targets the profile’s research, risk, and validation depth.*

### 1. Machine Learning & Statistical Modeling
- Supervised: gradient boosting (XGBoost, LightGBM), feature engineering, cross-validation, hyperparameter tuning.
- Unsupervised (when relevant): clustering for segmenting borrowers, PCA for risk factor decomposition.
- Time-series specialization: cointegration, vector autoregression, regime-switching models, feature engineering with lags.
- Book: *Advances in Financial Machine Learning* by Marcos López de Prado (focus on chapters about backtesting, feature importance, and meta-labeling).
- **Credit risk models:** Study IFRS 9 expected credit loss (ECL) framework, Probability of Default (PD), Loss Given Default (LGD), Exposure at Default (EAD). Implement a simplified Basel-style PD model for a loan portfolio.

### 2. Model Validation Rigor
- Framework: independent review of model design, data inputs, theoretical soundness, implementation testing, outcomes analysis (backtesting).
- Practice: take any model you built and write a formal validation report (executive summary, findings log, recommendations), mimicking SR 11-7 / OCC guidelines.
- Understand regulatory context for Danske Bank-like roles: stress testing, scenario analysis, capital adequacy.

### 3. Systematic Trading / Alpha Research
- Learn the research cycle: idea generation, data sourcing, signal construction, backtesting (with slippage, transaction costs, market impact), risk management.
- Tools: `zipline`/`backtrader` or build a simple vectorized backtesting engine in Python with realistic assumptions.
- Factor models: Fama-French, momentum, quality, low-volatility; cross-sectional and time-series frameworks.
- **Achievement goal:** “Developed a production-grade Python research pipeline and backtesting framework that streamlined signal discovery.”

### 4. Specialized Application Projects
- *Property valuation (Vurderingsstyrelsen):* Build an automated valuation model (AVM) using R and geospatial features, with rigorous hold-out testing.
- *Credit screening/relative value (Capital Four):* Use Python to analyze high-yield bond spreads vs fundamentals; build a rank-based relative value signal, backtest, and document clearly.
- *Statistical arbitrage (Leading Investment Firm):* Research mean-reversion on baskets, implement cointegration tests, and backtest with strict accounting for execution.

---
