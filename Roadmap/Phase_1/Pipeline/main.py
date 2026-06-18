"""
main.py – entry point for the full project.
Runs the data pipeline and then executes the test suite.
"""

import os
import sys
import subprocess
from pathlib import Path

# Add the project root and src to sys.path if needed
PROJECT_ROOT = Path(__file__).resolve().parent
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

# Optionally load .env file
try:
    from dotenv import load_dotenv
    load_dotenv(PROJECT_ROOT / ".env")
except ImportError:
    pass  # python-dotenv not installed – rely on already set env vars


def run_pipeline():
    """Run the data pipeline."""
    print("=" * 60)
    print("Running the data pipeline...")
    print("=" * 60)

    from fred_yahoo_pipeline import Pipeline, PipelineConfig

    config = PipelineConfig()
    pipeline = Pipeline(config)
    result = pipeline.run()
    print("\nPipeline finished. DataFrame shape:", result.shape)
    return result


def run_tests():
    """Run pytest on the tests/ folder."""
    print("\n" + "=" * 60)
    print("Running tests with pytest...")
    print("=" * 60)

    # Run pytest as a subprocess so it has its own clean environment
    result = subprocess.run(
        [sys.executable, "-m", "pytest", "tests/", "-v"],
        cwd=PROJECT_ROOT
    )
    sys.exit(result.returncode)


if __name__ == "__main__":
    # Step 1: Run the pipeline
    run_pipeline()

    # Step 2: Run the tests
    run_tests()