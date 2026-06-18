import pytest
import pandas as pd
import numpy as np
from unittest.mock import patch, MagicMock
from src.fred_yahoo_pipeline import DataCleaner, _clip_outliers

# Example: unit test for outlier clipping (pure function)
def test_clip_outliers_does_not_crash_empty_df():
    df = pd.DataFrame()
    result = _clip_outliers(df)
    assert result.empty

def test_clip_outliers_handles_single_column():
    df = pd.DataFrame({"A": [1, 2, 100]})  # 100 is an outlier
    clipped = _clip_outliers(df, k=2.0)
    assert clipped["A"].max() < 100
    assert clipped["A"].min() >= 1

# Mocking the FRED API to test DataFetcher
@patch("src.fred_yahoo_pipeline.Fred")
def test_fetch_fred_returns_df(mock_fred_class):
    mock_fred = MagicMock()
    mock_fred.get_series.return_value = pd.Series([1.0, 2.0, 3.0],
                                                  index=pd.date_range("2020-01-01", periods=3))
    mock_fred_class.return_value = mock_fred

    from src.fred_yahoo_pipeline import PipelineConfig, DataFetcher
    config = PipelineConfig(fred_api_key="fake", fred_series=("GDPC1",))
    fetcher = DataFetcher(config)
    df = fetcher.fetch_fred_data()
    assert isinstance(df, pd.DataFrame)
    assert "GDPC1" in df.columns
    assert len(df) == 3