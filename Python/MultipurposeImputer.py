




class MultipurposeImputer(TransformerMixin):
    """
        Impute missing values.

        Columns of dtype object are imputed with the most frequent value 
        in column.

        Columns of other types are imputed with mean of column.

    """

    def fit(self, X, y = None ):

        
        self.fill = pd.Series( # Converts the whole list into a pandas.Series object
            [ # generator is made if we use curly brackets () and a list is made if we use square brackets []
                X[var_col].value_counts().index[0] if X[var_col].dtype == np.dtype('O') else X[var_col].mean() for var_col in X # 'O' referst to datatype 'Object'
                ], index = X.columns # assigning back columns to the Series
            )

                    
        """
            The value_counts() function is used to get a Series containing counts of unique values.

            The resulting object will be in descending order so that the first element is the most frequently-occurring element.
            Excludes NA values by default

        """
        " index[0] here returns the (most frequent value at the top) top most value in the value_counts Series"
        """
            Series parameter index:
            indexarray-like or Index (1d)
            Values must be hashable and have the same length as data. Non-unique index values are allowed.
            Will default to RangeIndex (0, 1, 2, …, n) if not provided.
            If both a dict and index sequence are used, the index will override the keys found in the dict.

        """
        return self # The fit method should always return self


    def transform(self, X, y = None):
        return X.fillna(self.fill) # pandas.DataFrame.fillna : Fill NA/NaN values using the specified method.



