
class NullValuesFinder:

    " An object to help finding and handling null values in a dataframe "
   
    def __init__(self, data_frame, print_on = True): 
        # To switch off printing set print_on = False
        self.data_frame = data_frame
        self.print_on = print_on


    def checkForNullVals(self):
        " Checks if there are any null values in the whole dataset "

        count = 0
        for i in self.data_frame.columns:
            #print( f'{i} : ', self.data_frame[i].isnull().any())
            
            if self.data_frame[i].isnull().any():
                count += 1
                if self.print_on :
                    print(f'[NULL VALUES] There are null values in {i}')
                
        if count == 0:
            print('There are no null values in this dataset.') 
        elif count != 0:
            print(f"{count} columns out of {len(self.data_frame.columns)} in this dataset have null values.")       

    def NullColumnsList(self):
        " Returns a list with columns that have null values"

        null_col_list = []
        for i in self.data_frame.columns:
            #print( f'{i} : ', self.data_frame[i].isnull().any())
        
            if self.data_frame[i].isnull().any():
                #print(f'[NULL VALUES] There are null values in {i}')
                null_col_list.append(i)
        if self.print_on :
            print(f' There are null values in {null_col_list}.')
        return null_col_list
    
    def NullValCount(self, data_frame_column):
        " Takes a column name as parameter and returns the number of null values in that column "

        if data_frame_column in self.data_frame.columns:
            null_list = self.data_frame[data_frame_column].isnull().to_list()
            null_count = null_list.count(True)
            if self.print_on :
                print(f"The column '{data_frame_column}' has {null_count} null values.")
            return null_count
        else:
            print(f"ColumnError : Column '{data_frame_column}' was not found in object's columns")

    def NullValCountAll(self):
        "Returns a dictionary with all the column name and it's null value count as key, value pairs "

        null_dict = {}

        for data_frame_column in self.data_frame.columns:
            null_list = self.data_frame[data_frame_column].isnull().to_list()
            null_count = null_list.count(True)
            null_dict[data_frame_column] =  null_count
            #print(f"The column '{data_frame_column}' has {null_count} null values.")
        if self.print_on :
            print(null_dict)
        return null_dict

    def TotalRowCount(self):
        "Returns the total number of entries in a dataset"
        
        row_count = len(list(self.data_frame.index))
        if self.print_on :
            print(f"There are {row_count} entries in this dataset.")
        return row_count
