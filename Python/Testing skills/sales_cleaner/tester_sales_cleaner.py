import pytest
from sales_cleaner import CSVDataCleaner

def test_load_creates_dataframe(tmp_path):
    test_file = tmp_path / "test.csv"
    test_file.write_text(
        "Date ,   Product ,  Quantity, Price,Region  \n"
        "2025/09/1,    Laptop, 3.00, 210, USA\n"
        "09-09-2021  , Smartp#ho!ne**, 4.25, 111.02, GB\n"
        "2025-01-01, , 1, 1, BB\n"
        "2025-01-02,Tablet,34,890.00,VN\n"
        "2025-01-02,Tablet,34,890.00,VN\n"
        "2025-03-09,USB_Flash,55, , MP"
    )

    cleaner = CSVDataCleaner(str(test_file), "out_test_file.csv")
    
    cleaner.load()
    assert cleaner.data is not None
    assert cleaner.data.columns == ["Date", "Product", "Quantity", "Price", "Region"]
    assert len(cleaner.data) == 2
    cleaner.cleaner()
    assert cleaner.data["Product"].notna().all()
    assert cleaner.data["Price"].notna().all()
    assert all(cleaner.data["Total"] == cleaner.data["Quantity"] * cleaner.data["Price"])
    assert all(cleaner.data["Total"] > cleaner.min_total)
    assert cleaner.data["Quantity"].dtype() == int
    assert cleaner.data["Price"].dtype() == float
    assert len(cleaner.data) == 3
    for col in cleaner.data.select_dtypes(include=["object"]):
        assert cleaner.data[col].str.contains(r"[^\w\s]").sum == 0
        assert all(cleaner.data[col] == cleaner.data[col].str.strip())