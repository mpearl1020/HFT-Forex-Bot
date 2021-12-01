from easy_exchange_rates import API

currencies = [
    "KWD", "BHD", "OMR", "JOD", 
    "GBP", "KYD", "EUR", "CHF", 
    "USD", "BSD", "BMD", "PAB", 
    "CAD", "AUD", "SGD", "BND", 
    "NZD", "BGN", "FJD", "BRL"
]

# exchange rates from 12/1/21
if __name__ == '__main__':

    with open('exchange_rates.txt', 'a') as f:
        api = API()

        for t1 in currencies:
            for t2 in currencies:
                if t1 != t2:
                    time_series = api.get_exchange_rates(
                        base_currency = t1,
                        start_date = "2021-12-01",
                        end_date = "2021-12-01",
                        targets = [t2]
                    )
                    data_frame = api.to_dataframe(time_series)
                    f.write(f'{t1}\t{t2}\t{data_frame.iloc[0][t2]}\n')