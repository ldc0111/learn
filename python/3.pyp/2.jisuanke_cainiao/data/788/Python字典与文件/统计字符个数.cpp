def cnt_letter(string):
    t=(
        len([x for x in string if x.isalpha()]),
        len([x for x in string if x.isdigit()]),
        len([x for x in string if x== ' ']),
    )
    return t + (len(string) - sum(t),)

if __name__=="__main__":
    print "%d %d %d %d" % cnt_letter(raw_input())
