export type Person = {
    name: string;
    age: number;
    date_of_birth: Date;
}

export function Person_equals(obj1: Person, obj2: Person) {
    obj1.name == obj2.name &&
    obj1.age == obj2.age &&
    obj1.date_of_birth == obj2.date_of_birth
}
