"""
fred_yahoo_pipeline.py

A small, production-minded data pipeline that:
1. Fetches macroeconomic data from FRED and stock prices from Yahoo Finance.
2. Cleans and aligns the datasets.
3. Outputs summary statistics.

Demonstrates:
- Core Python: data structures (dataclasses, namedtuples, dicts), OOP, functional patterns
- Libraries: pandas, numpy, scipy, statsmodels, scikit-learn (simple scaling), matplotlib/seaborn
- Advanced: logging, pytest-ready design, type hints, docstrings (clean code)
- Project: virtual environment, package management, linter/formatter (black/flake8), Git branching
"""

import os

import logging
from dataclasses import dataclass
from datetime import datetime, timedelta
from typing import List, Optional, Tuple, Dict, Any
from functools import reduce

import numpy as np
import pandas as pd
import scipy.stats as stats
import statsmodels.api as sm
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
import seaborn as sns

from dotenv import load_dotenv
load_dotenv()

# Attempt imports; users install via requirements.txt
try:
    from fredapi import Fred
    import yfinance as yf
except ImportError as e:
    raise ImportError("Please install fredapi and yfinance: pip install fredapi yfinance") from e

# =============================================================================
# 1. Configuration & Logging (Clean Code: separation of concerns)
# =============================================================================

@dataclass(frozen=True)
class PipelineConfig:
    """Immutable configuration for the pipeline. (Data structure – dataclass)"""
    
    # API keys and parameters
    fred_api_key: str = os.getenv("FRED_API_KEY")
    if not fred_api_key:
        print("ERROR: FRED_API_KEY environment variable not set.")
        print("Set it via export/setx or a .env file with python-dotenv.")
        sys.exit(1)

    # Fred series to fetch (can be extended easily)
    lst_fred_series = (
                        # "GDPC1",    # Real Gross Domestic Product (quarterly)
                        )
    # Empty fred series
    fred_series: Tuple[str, ...] = ()
        # Try appending each of the lst_fred_series
    for series in lst_fred_series:
        try:
            # Test if series is valid by making a quick API call
            Fred(api_key=fred_api_key).get_series(series, observation_start="2020-01-01", observation_end="2020-01-31")
            fred_series += (series,)
        except Exception as e:
            logging.warning(f"FRED series {series} is invalid and will be skipped: {e}")

    # Yahoo tickers to fetch (can be extended easily)
    lst_yahoo_tickers = (
                        "^GSPC", # S&P 500 Index
                        "AAPL",  # Apple Inc. stock price
                        "NVDA",  # NVIDIA Corporation stock price
                        "MSFT",  # Microsoft Corporation stock price
                        "AVGO",  # Broadcom Inc. stock price
                        "MU",    # Micron Technology Inc. stock price
                        "AMD",   # Advanced Micro Devices Inc. stock price
                        "INTC",  # Intel Corporation stock price
                        "ORCL",  # Oracle Corporation stock price
                        "AMAT",  # Applied Materials Inc. stock price
                        "LRCX"   # Lam Research Corporation stock price
                        ) 
    
    # Empty yahoo tickers
    yahoo_tickers: Tuple[str, ...] = ()
        # Try appending each of the lst_yahoo_tickers
    for ticker in lst_yahoo_tickers:
        try: 
            yf.Ticker(ticker).history(period="1d")  # Test if ticker is valid
            yahoo_tickers += (ticker,)
        except Exception as e:
            logging.warning(f"Ticker {ticker} is invalid and will be skipped: {e}")
    
    start_date: str = "2023-01-01"
    # Yesterday's date as a string in YYYY-MM-DD format
    yesterday = (datetime.today() - timedelta(days=1)).strftime("%Y-%m-%d")
    end_date: Optional[str] = yesterday  # defaults to today
    print(f"PipelineConfig created with start_date={start_date} and end_date={end_date}")

def setup_logging(log_file: str = "pipeline.log") -> logging.Logger:
    """Configure logging to both file and console. (Clean code: robust logging)"""
    logger = logging.getLogger("pipeline")
    logger.setLevel(logging.DEBUG)
    formatter = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")

    fh = logging.FileHandler(log_file)
    fh.setLevel(logging.DEBUG)
    fh.setFormatter(formatter)
    logger.addHandler(fh)

    ch = logging.StreamHandler()
    ch.setLevel(logging.INFO)
    ch.setFormatter(formatter)
    logger.addHandler(ch)

    return logger

logger = setup_logging()

# =============================================================================
# 2. Data Fetcher – OOP with single responsibility
# =============================================================================

class DataFetcher:
    """
    Abstracted data fetching from multiple sources.
    Demonstrates OOP, use of instance attributes, and functional mapping.
    """

    def __init__(self, config: PipelineConfig) -> None:
        self.config = config
        # Encapsulate source-specific clients
        self.fred = Fred(api_key=config.fred_api_key)

    def fetch_fred_data(self) -> pd.DataFrame:
        """
        Fetch multiple FRED series and combine into a DataFrame.
        Uses a functional pattern: list comprehension + concat.
        """
        logger.info("Fetching FRED data for series: %s", self.config.fred_series)
        series_dict = {}
        for series_id in self.config.fred_series:
            try:
                # Function call using a closure (functional: mapping)
                series = self.fred.get_series(series_id,
                                              observation_start=self.config.start_date,
                                              observation_end=self.config.end_date)
                series_dict[series_id] = series
                logger.debug("Fetched %s, %d observations", series_id, len(series))
            except Exception as e:
                logger.error("Failed to fetch %s: %s", series_id, e)
                raise
        # Combine using pandas concat – data structure: dict -> DataFrame
        df = pd.DataFrame(series_dict)
        logger.info("FRED data shape: %s", df.shape)
        return df

    def fetch_yahoo_data(self) -> pd.DataFrame:
        """
        Download adjusted close prices from Yahoo Finance.
        Demonstrates list comprehension and error handling.
        """
        logger.info("Fetching Yahoo Finance data for tickers: %s", self.config.yahoo_tickers)
        end = self.config.end_date or datetime.today().strftime("%Y-%m-%d")
        data_frames = []
        for ticker in self.config.yahoo_tickers:
            try:
                ticker_obj = yf.Ticker(ticker)
                hist = ticker_obj.history(start=self.config.start_date, end=end)
                adj_close = hist[["Close"]].rename(columns={"Close": ticker})
                data_frames.append(adj_close)
                logger.debug("Fetched %s, %d rows", ticker, len(adj_close))
            except Exception as e:
                logger.error("Failed to fetch %s: %s", ticker, e)
                raise
        # Use reduce to merge functionally – pure function style
        df = reduce(lambda left, right: left.join(right, how="outer"), data_frames)
        logger.info("Yahoo data shape: %s", df.shape)
        return df

# =============================================================================
# 3. Data Cleaner – Mix of OOP and functional transformations
# =============================================================================

class DataCleaner:
    """Encapsulates all cleaning logic. Uses functional chaining via pandas."""

    @staticmethod
    def clean_fred(df: pd.DataFrame) -> pd.DataFrame:
        """
        Forward-fill missing values (typical for quarterly data like GDP),
        drop remaining NaNs, remove outliers using IQR.
        """
        logger.info("Cleaning FRED data...")
        # Functional: pipe transformations
        df_clean = (df
                    .ffill()    # handle missing
                    .dropna()                  # drop any still missing
                    .pipe(_clip_outliers)      # custom function applied via pipe
                    )
        logger.info("FRED clean shape: %s", df_clean.shape)
        return df_clean

    @staticmethod
    def clean_yahoo(df: pd.DataFrame) -> pd.DataFrame:
        """Interpolate missing stock prices and remove extreme spikes."""
        logger.info("Cleaning Yahoo data...")
        df_clean = (df
                    .interpolate(method="linear")
                    .dropna()
                    .pipe(_clip_outliers)
                    )
        logger.info("Yahoo clean shape: %s", df_clean.shape)
        return df_clean

    @staticmethod
    def align_datasets(fred: pd.DataFrame, yahoo: pd.DataFrame) -> pd.DataFrame:
        """
        Inner join on date index after normalizing timezones.
        Strips timezone info to avoid dtype conflicts in merge_asof.
        """
        logger.info("Aligning datasets...")

        # Make a copy to avoid mutating originals
        fred_aligned = fred.copy()
        yahoo_aligned = yahoo.copy()

        # Convert any tz-aware index to tz-naive (drop timezone)
        for df in (fred_aligned, yahoo_aligned):
            # 1. Remove timezone if present
            if df.index.tz is not None:
                df.index = df.index.tz_localize(None)
            # 2. Convert to common resolution (microseconds)
            df.index = pd.to_datetime(df.index).as_unit("us")

        # Optionally normalise to date only (if you only need daily alignment)
        # fred_aligned.index = fred_aligned.index.normalize()
        # yahoo_aligned.index = yahoo_aligned.index.normalize()

        # Merge on the now-consistent datetime index
        combined = pd.merge_asof(
            fred_aligned.sort_index(),
            yahoo_aligned.sort_index(),
            left_index=True,
            right_index=True,
            direction="forward"
        ).dropna()

        logger.info("Aligned shape: %s", combined.shape)
        return combined

def _clip_outliers(df: pd.DataFrame, k: float = 3.0) -> pd.DataFrame:
    """
    Pure function: clip outliers based on median absolute deviation (MAD).
    Shows scipy.stats usage and functional purity (no side-effects, returns new df).
    """
    for col in df.select_dtypes(include=[np.number]).columns:
        median = df[col].median()
        mad = stats.median_abs_deviation(df[col], scale="normal")
        lower = median - k * mad
        upper = median + k * mad
        df[col] = df[col].clip(lower, upper)
    return df

# =============================================================================
# 4. Analyzer – Statistical summaries & visualisation
# =============================================================================

class Analyzer:
    """
    Generates summary statistics, a regression summary, and a correlation heatmap.
    Shows statsmodels, scikit-learn, matplotlib, seaborn.
    """

    @staticmethod
    def summary_statistics(df: pd.DataFrame) -> pd.DataFrame:
        """Compute descriptive stats. Demonstrates numpy functions."""
        logger.info("Computing summary statistics...")
        stats_df = df.describe(percentiles=[0.25, 0.5, 0.75]).T
        stats_df["skewness"] = df.skew().values
        stats_df["kurtosis"] = df.kurtosis().values
        return stats_df

    @staticmethod
    def ols_regression(df: pd.DataFrame, y_col: str, x_cols: List[str]) -> sm.regression.linear_model.RegressionResultsWrapper:
        """Run a simple OLS regression. Demonstrates statsmodels."""
        logger.info("Running OLS: %s ~ %s", y_col, x_cols)
        X = sm.add_constant(df[x_cols])
        y = df[y_col]
        model = sm.OLS(y, X).fit()
        logger.info("OLS R-squared: %.4f", model.rsquared)
        return model

    @staticmethod
    def save_correlation_heatmap(df: pd.DataFrame, file_path: str = "correlation.png") -> None:
        """Plot and save a polished correlation heatmap with interpretation."""
        logger.info("Generating correlation heatmap to %s", file_path)
        corr = df.corr()

        # Clean, modern style
        plt.style.use("seaborn-v0_8-whitegrid")
        plt.rcParams.update({
            "font.family": "sans-serif",
            "font.sans-serif": ["DejaVu Sans", "Arial", "Helvetica"],
            "font.size": 14
        })

        fig, ax = plt.subplots(figsize=(12, 10.25))

        # Draw heatmap
        heatmap = sns.heatmap(
            corr,
            annot=True,
            fmt=".2f",
            annot_kws={"size": 11},
            cmap="coolwarm",
            center=0,
            vmin=-1,
            vmax=1,
            linewidths=0.1,
            linecolor="white",
            cbar_kws={
                "label": "Correlation Coefficient",
                "shrink": 0.8,
                "aspect": 20
            },
            ax=ax
        )

        # Title
        ax.set_title(
            "Feature Correlation Matrix",
            fontsize=20,
            fontweight="bold",
            pad=20,
            loc="center"
        )

        # Tick labels
        ax.set_xticklabels(ax.get_xticklabels(), rotation=45, ha="right", fontsize=12)
        ax.set_yticklabels(ax.get_yticklabels(), rotation=0, fontsize=12)

        # Colorbar formatting
        cbar = heatmap.collections[0].colorbar
        cbar.ax.set_ylabel("Correlation Coefficient", fontsize=13, labelpad=15)
        cbar.ax.tick_params(labelsize=11)

        # Explanatory text block – what correlations mean in context
        explanation = (
            "Correlation interpretation:\n"
            "• +1: Perfect positive linear relationship (variables move together)\n"
            "•  0: No linear relationship\n"
            "• −1: Perfect negative linear relationship (variables move opposite)\n"
            "\n"
            "• Strong correlations (|r| > 0.7) between predictors may indicate multicollinearity – this can make regression coefficients unstable.\n"
            "• Weak correlations (|r| < 0.3) suggest little linear association.\n"
            "• Moderate correlations are often acceptable but should be examined in the context of the model and domain knowledge."
        )

        # Reserve space at the bottom of the figure so the text doesn't overlap the plot
        plt.subplots_adjust(bottom=0.25)

        # Place the text in the reserved bottom margin
        fig.text(
            0.075, 0.025,               # x, y in figure coordinates (0 to 1)
            explanation,
            fontsize=10,
            ha="left",
            va="bottom",
            bbox=dict(
                facecolor="white",
                alpha=0.9,
                edgecolor="gray",
                boxstyle="round,pad=0.6"
            )
        )

        # Save with extra margin included
        plt.savefig(file_path, dpi=150, bbox_inches="tight")
        plt.close()
        logger.info("Heatmap saved.")

    @staticmethod
    def quick_model_check(model: sm.regression.linear_model.RegressionResultsWrapper) -> str:
        """
        Performs a quick sanity check on a fitted OLS model.
        Returns a one-line string: 'PASS' or 'FAIL' with reasons.
        """
        issues = []

        # 1. Durbin‑Watson – manually computed to avoid version‑specific attribute names
        residuals = model.resid
        if len(residuals) > 1:
            diff = np.diff(residuals)
            dw = np.sum(diff**2) / np.sum(residuals**2)
            if dw < 1.5 or dw > 2.5:
                issues.append(f"Autocorrelation (DW={dw:.2f}): should be ~2")  # rough rule of thumb

        # 2. Condition number > 30 indicates possible multicollinearity
        cond_num = model.condition_number
        if cond_num is not None and cond_num > 30:
            issues.append(f"Multicollinearity (Cond. No.={cond_num:.1f}): should be < 30")

        # 3. Jarque‑Bera test for residual normality (p < 0.05 -> non‑normal)
        from statsmodels.stats.stattools import jarque_bera
        jb_stat, jb_pvalue, skew, kurt = jarque_bera(model.resid)
        if jb_pvalue < 0.05:
            issues.append(f"Non‑normal residuals (JB p={jb_pvalue:.4f}): should be normal")

        # 4. Overall F‑test significance
        if model.f_pvalue > 0.05:
            issues.append("Model not significant (F-test p>0.05): should be significant")

        if issues:
            lines = ["⚠️ FAIL"]
            lines += [f"  • {issue}" for issue in issues]
            return "\n".join(lines)
        else:
            return "✅  PASS: basic diagnostics OK"

    @staticmethod
    def plot_time_series(df: pd.DataFrame, file_path: str = "time_series.png") -> None:
        """
        Create a two‑panel time‑series plot:
        - Top: GDPC1 (first column)
        - Bottom: Sum of min‑max normalized other variables, with individual components
        shown at low alpha.

        Thick yearly gridlines are drawn on both subplots, and there is zero vertical
        space between them.
        """
        logger.info("Generating time series plot to %s", file_path)

        plt.style.use("seaborn-v0_8-whitegrid")
        plt.rcParams.update({
            "font.family": "sans-serif",
            "font.sans-serif": ["DejaVu Sans", "Arial", "Helvetica"],
            "font.size": 14
        })

        # --- separate variables ---
        variables = df.columns.tolist()
        gdp_var = variables[0]               # GDPC1
        other_vars = variables[1:]           # all the rest

        # --- normalize each “other” variable to [0, 1] ---
        norm_others = df[other_vars].copy()
        for col in other_vars:
            col_min, col_max = df[col].min(), df[col].max()
            norm_others[col] = (df[col] - col_min) / (col_max - col_min)

        # sum of normalized components
        composite = norm_others.sum(axis=1)

        # --- create two subplots, zero vertical gap ---
        fig, (ax1, ax2) = plt.subplots(
            2, 1,
            figsize=(14, 7),
            sharex=True,
            gridspec_kw={"hspace": 0, "height_ratios": [1, 1]}
        )

        # ---- top panel: GDP ----
        ax1.plot(df.index, df[gdp_var], linewidth=1.8, color="#1f77b4")
            # If gdp_var is GSPC, add explanation in the title
        if gdp_var == "^GSPC":
            gdp_var = "S&P 500 Index"
        ax1.set_ylabel(gdp_var, fontsize=12, fontweight="bold")
        ax1.grid(True, axis="y", alpha=0.3)
        ax1.grid(False, axis="x")
        ax1.tick_params(labelsize=10)
        ax1.tick_params(labelbottom=False)   # hide x-labels on top panel

        # ---- bottom panel: composite + faint components ----
        # choose a colour for each component (qualitative palette)
        colors = plt.cm.tab10.colors  # up to 10 distinct colours
        for i, var in enumerate(other_vars):
            ax2.plot(
                df.index, norm_others[var],
                linewidth=0.8,
                color=colors[i % len(colors)],
                alpha=0.3,
                label=var
            )

        # composite line on top, bold
        ax2.plot(
            df.index, composite/len(other_vars),  # average of normalized components
            linewidth=2.2,
            color="#d62728",   # red
            label="Sum of normalized others"
        )

        ax2.set_ylabel("Largest Companies in Technology\nNormalized Composite", fontsize=12, fontweight="bold")
        ax2.grid(True, axis="y", alpha=0.3)
        ax2.grid(False, axis="x")
        ax2.tick_params(labelsize=10)

        # thin yearly vertical lines on both panels
        years = pd.date_range(
            start=df.index.min().replace(month=1, day=1),
            end=df.index.max().replace(month=12, day=31),
            freq="YS"
        )
        for year_date in years:
            ax1.axvline(x=year_date, color="black", linewidth=0.8, linestyle="-", alpha=0.4)
            ax2.axvline(x=year_date, color="black", linewidth=0.8, linestyle="-", alpha=0.4)

        # x‑axis formatting
        import matplotlib.dates as mdates
        ax2.xaxis.set_major_locator(mdates.YearLocator())
        ax2.xaxis.set_major_formatter(mdates.DateFormatter("%Y"))
        ax2.set_xlabel("Year", fontsize=13, fontweight="bold")

        # optional legend for bottom panel
        ax2.legend(loc="upper left", fontsize=9, ncol=2, frameon=True, facecolor="white", framealpha=0.8)

        # title
        fig.suptitle("Time Series of Stocks", fontsize=16, fontweight="bold", y=0.96)
        plt.tight_layout(rect=[0, 0, 1, 0.98])
        plt.savefig(file_path, dpi=150, bbox_inches="tight")
        plt.close()
        logger.info("Time series plot saved.")

# =============================================================================
# 5. Pipeline Orchestrator – Running the whole flow
# =============================================================================

class Pipeline:
    """Main orchestrator. High cohesion, encapsulates the entire flow."""

    def __init__(self, config: PipelineConfig) -> None:
        self.config = config
        self.fetcher = DataFetcher(config)
        self.cleaner = DataCleaner()
        self.analyzer = Analyzer()

    def run(self) -> pd.DataFrame:
        """Execute the pipeline and return the final aligned DataFrame."""
        logger.info("Pipeline started.")
        # Raw data fetching
        fred_raw = self.fetcher.fetch_fred_data()
        yahoo_raw = self.fetcher.fetch_yahoo_data()

        # Cleaning with functional chaining and clear separation of concerns
        fred_clean = self.cleaner.clean_fred(fred_raw)
        yahoo_clean = self.cleaner.clean_yahoo(yahoo_raw)

        # Align datasets on date index, handling timezone and resolution issues
            # Handle if one of the datasets is empty after cleaning
        if fred_clean.empty:
            logger.warning("FRED data is empty after cleaning.")
            aligned = yahoo_clean
        else:
            aligned = self.cleaner.align_datasets(fred_clean, yahoo_clean)

        # Save a time series plot of the aligned data for visual inspection
        self.analyzer.plot_time_series(aligned)

        # # Optional: scaling for machine learning readiness (sklearn)
        # scaler = StandardScaler()
        # scaled_data = scaler.fit_transform(aligned)
        # scaled_df = pd.DataFrame(scaled_data, index=aligned.index, columns=aligned.columns)
        # logger.info("Data scaled with StandardScaler (sklearn).")

        # Data acronyms:
        print("\n=== Data Acronyms ===")
        print("- GDPC1: Real Gross Domestic Product (quarterly)")
        print("- UNRATE: Unemployment Rate (monthly)")
        print("- CPIAUCSL: Consumer Price Index for All Urban Consumers (monthly)")
        print("- ^GSPC: S&P 500 Index (daily)")
        print("- AAPL: Apple Inc. stock price (daily)")
        print("")

        # Summary statistics
        summary = self.analyzer.summary_statistics(aligned)
        print("\n=== Summary Statistics ===")
        print(summary)

        # Print quick explanation of OLS regression 
        print("- Skewness: Measures the asymmetry of the distribution. Positive skew means a longer tail on the right, negative skew means a longer tail on the left.")
        print("- Kurtosis: Measures the 'tailedness' of the distribution. High kurtosis means more extreme outliers, low kurtosis means fewer outliers than a normal distribution.")
        print("")

        # Regression example (functional: list comprehension for feature selection)
        if len(aligned.columns) > 1:
            numeric_cols = aligned.select_dtypes(include=[np.number]).columns.tolist()
            y_var = numeric_cols[0]  # For demonstration, we can loop through each numeric column as a dependent variable
            # for y_var in numeric_cols:
            x_vars = [c for c in numeric_cols if c != y_var]  # functional filtering
            if x_vars:
                model = self.analyzer.ols_regression(aligned, y_var, x_vars)
                print(f"\n=== OLS Regression: {y_var} ===")
                print(model.summary())
                # Quick verdict
                verdict = self.analyzer.quick_model_check(model)
                print("\nModel diagnostic verdict:", verdict)
                print("")

        if verbose := False:  # Set to True to print detailed interpretation notes
            # Print notes on interpreting the results
            print("\n=== Interpretation Notes ===")
            print("t-statistic: Measures how many standard deviations the coefficient is away from zero. A higher absolute t-value indicates a more significant predictor.")
            print("P>|t|: The p-value for each coefficient tests the null hypothesis that the coefficient is zero (no effect). A low p-value (< 0.05) suggests the variable is a significant predictor of the dependent variable.")
            print("Prob(Omnibus)/Prob(JB): The p-values for the Omnibus and Jarque-Bera tests. A low value (< 0.05) indicates that the residuals do not follow a normal distribution.")
            print("Jarque-Bera (JB): Tests if the data has the skewness and kurtosis matching a normal distribution. A high JB statistic with a low p-value suggests non-normality.")
            print("Omnibus: Tests the skewness and kurtosis of the residuals. Similar to JB, a high statistic with a low p-value indicates non-normality.")
            print("Durbin-Watson: Tests for autocorrelation in the residuals. Values around 2 suggest no autocorrelation, values < 2 suggest positive autocorrelation, and values > 2 suggest negative autocorrelation.")

            # Print quick explanation of correlation heatmap
            print("\n- Correlation Heatmap: Shows pairwise correlations between features. Values close to 1 or -1 indicate strong positive or negative relationships, respectively. Values near 0 indicate weak or no linear relationship.")
            print("- Interpreting the heatmap: Look for strong correlations (dark colors) to identify potential relationships. Be cautious of spurious correlations, especially in small datasets.")
            print("- OLS: Ordinary Least Squares regression estimates the relationship between a dependent variable and one or more independent variables.")
            print("- R-squared: Indicates how well the independent variables explain the variance in the dependent variable, with values closer to 1 indicating a better fit.")
            print("")

        # Heatmap
        self.analyzer.save_correlation_heatmap(aligned)

        logger.info("Pipeline finished successfully.")
        return aligned

# =============================================================================
# 6. Main guard and configuration example
# =============================================================================

if __name__ == "__main__":
    import os

    # API key from environment variable (best practice)
    FRED_API_KEY = os.getenv("FRED_API_KEY")
    if not FRED_API_KEY:
        raise ValueError("Set the FRED_API_KEY environment variable.")

    config = PipelineConfig(
        fred_api_key=FRED_API_KEY
    )

    pipeline = Pipeline(config)
    final_data = pipeline.run()