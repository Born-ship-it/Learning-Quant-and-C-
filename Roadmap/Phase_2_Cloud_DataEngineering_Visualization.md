
## Phase 2: Cloud, Data Engineering & Visualization (Months 6–18)
*Build the architecture skills that the profile labels “Data/Cloud Roles”.*

### 1. Cloud Platform & Warehousing
- Pick **Azure + Databricks + Snowflake** as primary combo (matches the profile’s emphasis).  
  - Azure: provision storage accounts, understand ADLS Gen2, key vaults, basic networking.  
  - Databricks: Spark fundamentals (PySpark), Delta Lake, medallion architecture (bronze/silver/gold).  
  - Snowflake: virtual warehouses, time-travel, cloning, role-based access.
- Optional: Light touch AWS/GCP to show breadth (e.g., deploy a simple Lambda function or Cloud Run service).

### 2. Data Engineering Patterns
- ETL vs ELT; incremental loads, CDC (change data capture) logic.
- Orchestration: start with Databricks Workflows/Azure Data Factory, then explore Airflow (self-hosted or Astronomer) or dbt Cloud.
- dbt: data modeling, tests, documentation, snapshots. Build a dbt project that transforms raw financial data into a clean dimensional model (facts, dimensions).
- **Achievement goal:** “Built and maintained end-to-end data pipelines ensuring automated delivery of signals/reports.”

### 3. Data Modeling for Analytics
- Dimensional modeling (Kimball): fact tables, slowly changing dimensions, bridge tables for multi-valued dimensions.
- Semantic layers: experience with Power BI’s dataset modeling or dbt’s semantic layer.
- **Visualization:** Master Power BI (DAX, performance optimization, Row-Level Security). Replicate a complex financial dashboard from a template.

### 4. Project: Full-Stack Analytics Solution
- Use Azure + Databricks/Snowflake + dbt + Power BI to ingest public credit data, model it, and surface key metrics (e.g., credit spread trends, sector breakdowns) in a dashboard.
- Apply software development practices: Git, code reviews, CI/CD (GitHub Actions or Azure DevOps) for dbt and visualization deployment.

---
